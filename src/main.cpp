#include "repository/AulaRepository.h"
#include "repository/databaseManager.h"
#include <iostream>

void exibirMenuPrincipal();
void agendarNovaAula(AulaRepository &aulaRepo);
void inscreverPraticanteEmAula(AulaRepository &aulaRepo);
void gerenciarAulas(AulaRepository &aulaRepo);

int main()
{

  // ------ INICIALIZAÇÃO DO BANCO DE DADOS ------
  DatabaseManager dbManager;

  const std::string dbPath = "yoga_studio.db";
  const std::string schemaPath = "../database/schema.sql";

  if (!dbManager.abrirConexao(dbPath))
  {
    std::cerr
        << "[ERRO FATAL] Não foi possível abrir ou criar o banco de dados em: "
        << dbPath << std::endl;
    return 1;
  }
  std::cout << "[SUCESSO] Conexão com o banco de dados aberta." << std::endl;

  if (!dbManager.inicializarTabelas(schemaPath))
  {
    std::cerr << "[ERRO] Não foi possível inicializar as tabelas" << std::endl;
    return 1;
  }
  // ------ FIM DA INICIALIZAÇÃO DO BANCO DE DADOS ------

  // ------ INICIALIZAÇÃO DOS REPOSITÓRIOS ------
  AulaRepository aulaRepo(dbManager.getDBHandle());

  // Meninas, vocês irão adicionar aqui a inicialização dos outros repositórios
  // ------ FIM DA INICIALIZAÇÃO DOS REPOSITÓRIOS ------

  int escolha = -1;
  while (true)
  {
    exibirMenuPrincipal();
    std::cin >> escolha;

    switch (escolha)
    {
    case 1:
      std::cout << "Gerenciar Aulas selecionado." << std::endl;
      gerenciarAulas(aulaRepo);

      break;
    case 2:
      std::cout << "Gerenciar Praticantes selecionado." << std::endl;
      // Chamar função para gerenciar praticantes
      break;
    case 3:
      std::cout << "Gerenciar Instrutores selecionado." << std::endl;
      // Chamar função para gerenciar instrutores
      break;
    case 4:
      std::cout << "Gerenciar Tipos de Aula selecionado." << std::endl;
      // Chamar função para gerenciar tipos de aula
      break;
    case 0:
      std::cout << "Saindo do sistema. Até logo!" << std::endl;
      return 0;
    default:
      std::cout << "Opção inválida. Tente novamente." << std::endl;
    }
  }
  return 0;
}

void exibirMenuPrincipal()
{
  std::cout << "===== Sistema de Gerenciamento do Estúdio de Yoga ====="
            << std::endl;
  std::cout << "1. Gerenciar Aulas" << std::endl;
  std::cout << "2. Gerenciar Praticantes" << std::endl;
  std::cout << "3. Gerenciar Instrutores" << std::endl;
  std::cout << "4. Gerenciar Tipos de Aula" << std::endl;
  std::cout << "0. Sair" << std::endl;
  std::cout << "Escolha uma opção: ";
}

void gerenciarAulas(AulaRepository &aulaRepo)
{
  int escolha = -1;
  while (true)
  {
    std::cout << "===== Gerenciamento de Aulas =====" << std::endl;
    std::cout << "1. Agendar Nova Aula" << std::endl;
    std::cout << "2. Inscrever Praticante em Aula" << std::endl;
    std::cout << "3. Listar Aulas" << std::endl;
    std::cout << "0. Voltar ao Menu Principal" << std::endl;
    std::cout << "Escolha uma opção: ";
    std::cin >> escolha;

    switch (escolha)
    {
    case 1:
      agendarNovaAula(aulaRepo);
      break;
    case 2:
      inscreverPraticanteEmAula(aulaRepo);
      break;
    case 3:
      aulaRepo.listarAulas();
      break;
    case 0:
      return;
    default:
      std::cout << "Opção inválida. Tente novamente." << std::endl;
    }
  }
}

void agendarNovaAula(AulaRepository &aulaRepo)
{
  std::string dataHora;
  int capacidade, tipoDeAulaId, instrutorId;

  std::cout << "Digite a data e hora da aula (formato DD/MM/AAAA HH:MM): ";
  std::cin.ignore(); // Limpar o buffer antes de usar getline
  std::getline(std::cin, dataHora);
  std::cout << "Digite a capacidade máxima da aula: ";
  std::cin >> capacidade;
  std::cout << "Digite o ID do tipo de aula: ";
  std::cin >> tipoDeAulaId;
  std::cout << "Digite o ID do instrutor: ";
  std::cin >> instrutorId;

  int novoId =
      aulaRepo.agendarAula(dataHora, capacidade, tipoDeAulaId, instrutorId);
  if (novoId != -1)
  {
    std::cout << "Aula agendada com sucesso! ID da Aula: " << novoId
              << std::endl;
  }
  else
  {
    std::cout << "Falha ao agendar a aula." << std::endl;
  }
}

void inscreverPraticanteEmAula(AulaRepository &aulaRepo)
{
  int praticanteId, aulaId;

  std::cout << "Digite o ID do praticante: ";
  std::cin >> praticanteId;
  std::cout << "Digite o ID da aula: ";
  std::cin >> aulaId;

  if (aulaRepo.inscreverPraticanteEmAula(praticanteId, aulaId))
  {
    std::cout << "Praticante inscrito com sucesso na aula!" << std::endl;
  }
  else
  {
    std::cout << "Falha ao inscrever o praticante na aula verifique os IDs"
              << std::endl;
  }
}
