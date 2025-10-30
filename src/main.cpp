#include "repository/databaseManager.h"
#include <iostream>

/**
 * @brief Popula o banco de dados com a massa de dados mínima
 * para que os testes de inscrição possam ser executados.
 * Usamos "INSERT OR IGNORE" para que este script
 * possa ser rodado várias vezes sem causar erros "UNIQUE constraint".
 */
void popularDadosDeTeste(DatabaseManager &dbManager) {
  std::cout << "--- Populando dados de teste ---" << std::endl;

  // 1. Criar pré-requisitos (Plano, Instrutor, TipoDeAula)
  dbManager.executarSQLSimples("INSERT OR IGNORE INTO Plano (id, nome, preco) "
                               "VALUES (1, 'Plano Teste', 99.99);");
  dbManager.executarSQLSimples(
      "INSERT OR IGNORE INTO Instrutor (id, nome, email, especialidade) VALUES "
      "(1, 'Instrutor Teste', 'instrutor@teste.com', 'Hatha');");
  dbManager.executarSQLSimples(
      "INSERT OR IGNORE INTO TipoDeAula (id, nome, descricao) VALUES (1, 'Aula "
      "Teste', 'Aula de teste');");

  // 2. Criar Praticante e Aula que dependem dos IDs acima
  dbManager.executarSQLSimples(
      "INSERT OR IGNORE INTO Praticante (id, nome, email, plano_id) VALUES (1, "
      "'Aluno Teste', 'aluno@teste.com', 1);");
  dbManager.executarSQLSimples(
      "INSERT OR IGNORE INTO Aula (id, dataHora, capacidadeMaxima, "
      "instrutor_id, tipo_aula_id) VALUES (1, '30/10/2025 18:00', 10, 1, 1);");

  // Inserir um segundo praticante para mais testes
  dbManager.executarSQLSimples(
      "INSERT OR IGNORE INTO Praticante (id, nome, email, plano_id) VALUES (2, "
      "'Outra Aluna', 'outra@teste.com', 1);");

  std::cout << "--- Dados de teste populados ---" << std::endl;
}

int main() {
  DatabaseManager dbManager;

  const std::string dbPath = "yoga_studio.db";
  const std::string schemaPath = "../database/schema.sql";

  // 1. Abrir conexão
  if (!dbManager.abrirConexao(dbPath)) {
    std::cerr << "Falha ao abrir o banco de dados." << std::endl;
    return 1;
  }

  // 2. Criar as tabelas (Se já existirem, o IF NOT EXISTS protege)
  if (!dbManager.inicializarTabelas(schemaPath)) {
    std::cerr << "Falha ao inicializar as tabelas." << std::endl;
    return 1;
  }

  // 3. Criar os dados de teste (Praticante 1, Aula 1, etc.)
  popularDadosDeTeste(dbManager);

  // --- INÍCIO DO TESTE POST/GET ---

  // IDs de teste (sabemos que eles são '1' e '2' por causa da função acima)
  int idPraticante1 = 1;
  int idPraticante2 = 2;
  int idAula1 = 1;

  std::cout << "\n--- TESTANDO 'POST' (INSERT) ---" << std::endl;
  // Usamos "INSERT OR IGNORE" na tabela Participa (Inscrição)
  // para que o teste não falhe se o vínculo já existir.
  dbManager.executarSQLSimples("INSERT OR IGNORE INTO Participa "
                               "(praticante_id, aula_id) VALUES (1, 1);");
  // Vamos chamar diretamente o método que criamos:
  // (Note que se já inserimos acima, este dará "false" se tivermos
  //  uma constraint UNIQUE, mas como não temos, ele só insere de novo,
  //  mas nossa PRIMARY KEY (praticante_id, aula_id) no schema.sql
  //  vai impedir a duplicata!)

  // Vamos tentar inscrever o Praticante 1 (de novo)
  std::cout << "Tentando inscrever Praticante 1 na Aula 1 (deve falhar se já "
               "inscrito)..."
            << std::endl;
  dbManager.inserirInscricao(idPraticante1,
                             idAula1); // O SQL correto para Participa é PRIMARY
                                       // KEY, então ele falhará (o que é bom)

  // Vamos inscrever o Praticante 2 (que é novo)
  std::cout << "Tentando inscrever Praticante 2 na Aula 1..." << std::endl;
  dbManager.inserirInscricao(idPraticante2, idAula1);

  std::cout << "\n--- TESTANDO 'GET' (SELECT) ---" << std::endl;
  // Agora vamos validar quem REALMENTE está na aula 1
  // Devemos ver "Aluno Teste" e "Outra Aluna"
  dbManager.validarInscritosNaAula(idAula1);

  // --- FIM DO TESTE ---

  return 0;
}
