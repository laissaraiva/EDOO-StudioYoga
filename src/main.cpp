#include "repository/databaseManager.h"
#include <iostream>

int main()
{
  DatabaseManager dbManager;

  const std::string dbPath = "yoga_studio.db";
  const std::string schemaPath = "../database/schema.sql";

  if (!dbManager.abrirConexao(dbPath))
  {
    std::cerr << "[ERRO FATAL] Não foi possível abrir ou criar o banco de dados em: " << dbPath << std::endl;
    return 1; // Retorna um código de erro
  }
  std::cout << "[SUCESSO] Conexão com o banco de dados aberta." << std::endl;

  if(!dbManager.inicializarTabelas(schemaPath))
  {
    std::cerr << "[ERRO] Não foi possível inicializar as tabelas" << std::endl;
  }
  std::cout << "[SUCESSO] Tabelas inicializadas!" << std::endl;

  std::cout << "Teste finalizado com sucesso!!" << std::endl;

  return 0;
}
