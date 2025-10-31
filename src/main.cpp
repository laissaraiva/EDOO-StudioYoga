#include "repository/AulaRepository.h"
#include "repository/databaseManager.h"
#include <iostream>

void popularDadosDeTeste(DatabaseManager &dbManager) {
  std::cout << "--- Populando dados de teste ---" << std::endl;
  // (Precisamos garantir que DatabaseManager tenha 'executarSQLSimples'
  // como tínhamos no teste anterior)

  // 1. Criar pré-requisitos (Plano, Instrutor, TipoDeAula)
  dbManager.executarSQLSimples("INSERT OR IGNORE INTO Plano (id, nome, preco) "
                               "VALUES (1, 'Plano Teste', 99.99);");
  dbManager.executarSQLSimples(
      "INSERT OR IGNORE INTO Instrutor (id, nome, email, especialidade) VALUES "
      "(1, 'Instrutor Teste', 'instrutor@teste.com', 'Hatha');");
  dbManager.executarSQLSimples(
      "INSERT OR IGNORE INTO TipoDeAula (id, nome, descricao) VALUES (1, 'Aula "
      "Teste', 'Aula de teste');");

  // 2. Criar Praticante
  dbManager.executarSQLSimples(
      "INSERT OR IGNORE INTO Praticante (id, nome, email, plano_id) VALUES (1, "
      "'Aluno Teste', 'aluno@teste.com', 1);");
  std::cout << "--- Dados de teste populados ---" << std::endl;
}

int main() {
  DatabaseManager dbManager;

  const std::string dbPath = "yoga_studio.db";
  const std::string schemaPath = "../database/schema.sql";

  if (!dbManager.abrirConexao(dbPath)) {
    std::cerr
        << "[ERRO FATAL] Não foi possível abrir ou criar o banco de dados em: "
        << dbPath << std::endl;
    return 1; // Retorna um código de erro
  }
  std::cout << "[SUCESSO] Conexão com o banco de dados aberta." << std::endl;

  if (!dbManager.inicializarTabelas(schemaPath)) {
    std::cerr << "[ERRO] Não foi possível inicializar as tabelas" << std::endl;
    return 1;
  }

  // Popular dados de teste
  popularDadosDeTeste(dbManager);

  AulaRepository repoAula(dbManager.getDBHandle());

  int novoIdAula = repoAula.agendarAula("01/11/2025 10:00", 15, 1, 1);

  if (novoIdAula == -1) {
    std::cerr << "Falha ao agendar a aula!" << std::endl;
    return 1;
  }

  if (!repoAula.inscreverPraticanteEmAula(1, novoIdAula)) {
    std::cerr << "Falha ao inscrever o praticante!" << std::endl;
    return 1;
  }

  // 4. Teste de Duplicidade (Opcional)
  std::cout << "Tentando inscrever o mesmo Praticante 1 de novo..."
            << std::endl;
  repoAula.inscreverPraticanteEmAula(1, novoIdAula);
  // (Deve imprimir a mensagem "já estava inscrito")

  std::cout << "\n--- Teste de POST concluído com sucesso ---" << std::endl;
  return 0;
}
