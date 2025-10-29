#include "databaseManager.h" // (Supondo que você criou o .h)
#include <iostream>

int main() {
  DatabaseManager dbManager;

  const std::string dbPath = "yoga_studio.db";
  const std::string schemaPath = "../database/schema.sql";

  if (dbManager.abrirConexao(dbPath)) {

    dbManager.inicializarTabelas(schemaPath);

  } else {
    std::cerr
        << "Não foi possível iniciar o sistema pois o banco de dados não abriu."
        << std::endl;
    return 1;
  }

  std::cout << "Bem vindo ao Sistema do Studio de Yoga!" << std::endl;

  return 0;
}
