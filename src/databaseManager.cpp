// 1. Inclua a "planta" da classe que você está construindo
#include "databaseManager.h"

// 2. Inclua o que você precisa para a implementação
#include <fstream>
#include <iostream>
#include <sstream>

// Implementação do Construtor
DatabaseManager::DatabaseManager() : db(nullptr) {
  // Começa com o banco fechado (ponteiro nulo)
}

// Implementação do Destrutor
DatabaseManager::~DatabaseManager() {
  if (db) {
    sqlite3_close(db);
    std::cout << "Conexão com o banco de dados fechada." << std::endl;
  }
}

// Implementação do método de abrir
bool DatabaseManager::abrirConexao(const std::string &nomeArquivo) {
  int rc = sqlite3_open(nomeArquivo.c_str(), &db);

  if (rc != SQLITE_OK) {
    std::cerr << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db)
              << std::endl;
    return false;
  } else {
    std::cout << "Banco de dados aberto com sucesso: " << nomeArquivo
              << std::endl;
    return true;
  }
}

bool DatabaseManager::inicializarTabelas(const std::string &schemaSqlPath) {
  if (!db) {
    std::cerr << "Erro: Banco de dados não está aberto." << std::endl;
    return false;
  }

  std::ifstream schemaFile(schemaSqlPath);
  if (!schemaFile.is_open()) {
    std::cerr << "Erro ao abrir o arquivo schema.sql em: " << schemaSqlPath
              << std::endl;
    return false;
  }

  std::stringstream buffer;
  buffer << schemaFile.rdbuf();
  std::string schemaSql = buffer.str();
  schemaFile.close();

  char *errMsg = nullptr;

  int rc = sqlite3_exec(db, schemaSql.c_str(), nullptr, nullptr, &errMsg);

  if (rc != SQLITE_OK) {
    std::cerr << "Erro ao executar o schema SQL: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return false;
  }

  std::cout << "Tabelas do banco de dados inicializadas com sucesso."
            << std::endl;
  return true;
}

bool DatabaseManager::inserirInscricao(int praticanteId, int aulaId) {
  if (!db) {
    std::cerr << "Erro: Banco de dados não está aberto." << std::endl;
    return false;
  }

  // 1. O "Template" SQL com placeholders (?)
  const char *sql =
      "INSERT INTO Participa (praticante_id, aula_id) VALUES (?, ?);";

  sqlite3_stmt *stmt = nullptr; // O "statement" preparado

  // 2. PREPARE: Compila o template SQL e cria o objeto "stmt"
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Erro ao preparar statement (INSERT): " << sqlite3_errmsg(db)
              << std::endl;
    return false;
  }

  // 3. BIND: Liga as variáveis C++ aos placeholders (?)
  // O 1º '?' tem índice 1
  sqlite3_bind_int(stmt, 1, praticanteId);
  // O 2º '?' tem índice 2
  sqlite3_bind_int(stmt, 2, aulaId);

  // 4. STEP: Executa o comando
  // Para INSERT/UPDATE/DELETE, esperamos SQLITE_DONE
  if (sqlite3_step(stmt) != SQLITE_DONE) {
    std::cerr << "Erro ao executar statement (INSERT): " << sqlite3_errmsg(db)
              << std::endl;
    sqlite3_finalize(stmt); // Limpa o statement antes de sair
    return false;
  }

  // 5. FINALIZE: Limpa o statement da memória
  sqlite3_finalize(stmt);

  std::cout << "[DB] Praticante " << praticanteId << " inscrito na aula "
            << aulaId << " com sucesso." << std::endl;
  return true;
}

void DatabaseManager::validarInscritosNaAula(int aulaId) {
  if (!db)
    return;

  // Queremos selecionar o NOME do praticante, então precisamos
  // "juntar" (JOIN) as tabelas Participa e Praticante.
  const char *sql = "SELECT p.nome FROM Praticante p "
                    "JOIN Participa ins ON p.id = ins.praticante_id "
                    "WHERE ins.aula_id = ?;";

  sqlite3_stmt *stmt = nullptr;

  // 1. PREPARE
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Erro ao preparar statement (SELECT): " << sqlite3_errmsg(db)
              << std::endl;
    return;
  }

  // 2. BIND (Ligamos o ID da aula ao placeholder)
  sqlite3_bind_int(stmt, 1, aulaId);

  std::cout << "\n--- Validando Inscritos na Aula " << aulaId << " ---"
            << std::endl;

  // 3. STEP (em loop)
  // Continuamos chamando _step() enquanto ele retornar SQLITE_ROW
  // Isso significa que ele encontrou uma linha de resultado.
  while (sqlite3_step(stmt) == SQLITE_ROW) {

    // 4. COLUMN: Pega os dados da linha atual
    // Os índices da coluna começam em 0
    const unsigned char *nome = sqlite3_column_text(stmt, 0);

    std::cout << " - Praticante: " << nome << std::endl;
  }
  // (O loop termina quando _step() retorna SQLITE_DONE)

  std::cout << "-----------------------------------" << std::endl;

  // 5. FINALIZE
  sqlite3_finalize(stmt);
}

bool DatabaseManager::executarSQLSimples(const std::string &sql) {
  if (!db)
    return false;

  char *errMsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
    std::cerr << "Erro em SQL simples: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return false;
  }
  return true;
}
