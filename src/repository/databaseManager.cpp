// 1. Inclua a "planta" da classe que você está construindo
#include "repository/databaseManager.h"

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

// Implementação do método para obter o ponteiro do banco de dados
sqlite3 *DatabaseManager::getDBHandle() { return db; }
