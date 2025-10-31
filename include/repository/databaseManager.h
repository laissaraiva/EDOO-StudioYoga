#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "sqlite3.h" // Inclui o sqlite para que ele saiba o que é "sqlite3*"
#include <string>

class DatabaseManager {
private:
  sqlite3 *db; // O ponteiro para o objeto do banco de dados

public:
  DatabaseManager();  // Construtor
  ~DatabaseManager(); // Destrutor

  // Método para abrir a conexão
  bool abrirConexao(const std::string &nomeArquivo);

  bool inicializarTabelas(const std::string &schemaSqlPath);

  sqlite3 *getDBHandle(); // Fornece a conexão para os repositórios
  

  //Métodos para teste
  bool executarSQLSimples(const std::string& sql);
};

#endif
