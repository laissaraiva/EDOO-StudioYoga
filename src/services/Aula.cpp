#include "services/Aula.h"
#include "services/Praticante.h" // Para poder chamar praticante->getId()
#include <string>
#include <iostream>

Aula ::Aula(int id, const std::string &dataHora, int capacidade,
            TipoDeAula *tipo, Instrutor *instr)
    : id(id), capacidadeMaxima(capacidade), tipoDeAula(tipo), instrutor(instr),
      dataHora(dataHora) {}

Aula::~Aula() {}

// --- GETTERS ---
int Aula::getId() const { return this->id; }
int Aula::getCapacidadeMaxima() const { return this->capacidadeMaxima; }
int Aula::getNumeroDePraticantesInscritos() const { return this->praticantesInscritos.size(); }
TipoDeAula *Aula::getTipoDeAula() const { return this->tipoDeAula; }
Instrutor *Aula::getInstrutor() const { return this->instrutor; }
std::string Aula::getDataHora() const { return this->dataHora; }
const std::vector<Praticante *> &Aula::getPraticantesInscritos() const { return this->praticantesInscritos; }

// --- SETTERS ---
void Aula::setCapacidadeMaxima(int capacidade)
{
  if (capacidade <= 0)
  {
    std::cerr << "[ERRO] Capacidade deve ser maior que zero." << std::endl;
    return;
  }

  if (capacidade < static_cast<int>(praticantesInscritos.size()))
  {
    std::cerr << "[ERRO] Capacidade não pode ser menor que o número de praticantes já inscritos ("
              << praticantesInscritos.size() << ")." << std::endl;
    return;
  }

  this->capacidadeMaxima = capacidade;
}

void Aula::setTipoDeAula(TipoDeAula *tipo)
{
  if (tipo == nullptr)
  {
    std::cerr << "[ERRO] O ponteiro recebido como parâmetro no método setTipoDeAula não pode ser nulo!" << std::endl;
    return;
  }

  this->tipoDeAula = tipo;
}

void Aula::setInstrutor(Instrutor *instr)
{
  if (instr == nullptr)
  {
    std::cerr << "[ERRO] O ponteiro recebido como parâmetro no método setInstrutor não pode ser nulo!" << std::endl;
    return;
  }

  this->instrutor = instr;
}

void Aula::setDataHora(const std::string &novaDataHora)
{

  if (novaDataHora.empty())
  {
    std::cerr << "Erro: A data/hora não pode ser vazia." << std::endl;
    return;
  }

  const int TAMANHO_ESPERADO = 16;

  if (novaDataHora.length() != TAMANHO_ESPERADO)
  {
    std::cerr << "Erro: Formato de data/hora inválido. "
              << "Esperado 'DD/MM/AAAA HH:MM'." << std::endl;
    return;
  }

  if (novaDataHora[2] != '/' || novaDataHora[5] != '/' ||
      novaDataHora[10] != ' ' || novaDataHora[13] != ':')
  {
    std::cerr << "Erro: Formato de data/hora inválido. "
              << "Separadores incorretos." << std::endl;
    return;
  }

  this->dataHora = novaDataHora;
}

// --- REGRAS DE NEGÓCIO ---

bool Aula::adicionarPraticante(Praticante *praticante)
{
  if (praticante == nullptr)
  {
    std::cerr << "[ERRO] O ponteiro recebido pelo método adicionarPraticante não pode ser nulo!" << std::endl;
    return false;
  }

  if (this->getCapacidadeMaxima() - this->getNumeroDePraticantesInscritos() == 0)
  {
    std::cerr << "[ERRO] Aula lotada!" << std::endl;
    return false;
  }

  for (const auto &p : praticantesInscritos)
  {
    if (p->getId() == praticante->getId())
    {
      std::cerr << "[ERRO] Praticante já está inscrito nesta aula." << std::endl;
      return false;
    }
  }

  this->praticantesInscritos.push_back(praticante);
  return true;
}

bool Aula::removerPraticante(Praticante *praticante)
{
  if (praticante == nullptr)
  {
    std::cerr << "[ERRO] Ponteiro praticante do método removerPraticante é nulo." << std::endl;
    return false;
  }

  for (auto it = this->praticantesInscritos.begin(); it != this->praticantesInscritos.end(); ++it)
  {
    if ((*it)->getId() == praticante->getId())
    {
      this->praticantesInscritos.erase(it);
      return true;
    }
  }
  return false;
}

int Aula::verificarVagas() const
{
  return this->getCapacidadeMaxima() - this->getNumeroDePraticantesInscritos();
}

void Aula::listarPraticantesInscritos() const
{
  // TO-DO: Adicionar o getPlano()->getNome() depois
  std::cout << " --------------PRATICANTES INSCRITOS--------------" << std::endl;
  for (auto it = this->praticantesInscritos.begin(); it != this->praticantesInscritos.end(); ++it)
  {
    std::cout << (*it)->getId() << (*it)->getNome() << (*it)->getPlano() << std::endl;
  }
}

void Aula::exibirDetalhesCompletos() const
{
  // TO-DO: Preciso após implementação das classes praticantes e tipo de aula, retornar o nome do instrutor e o nome do tipo de aula, ao invés de retornar o objeto inteiro
  int aulaId = this->getId();
  int capacidadeMaxima = this->getCapacidadeMaxima();
  int numPraticantes = this->getNumeroDePraticantesInscritos();
  TipoDeAula *tpAula = this->getTipoDeAula();
  Instrutor *inst = this->getInstrutor();
  std::string dH = this->getDataHora();

  std::cout << "--------------DETALHES DA AULA--------------" << std::endl
            << "Id: " << aulaId << std::endl
            << "Capacidade: " << capacidadeMaxima << std::endl
            << "Número de praticantes: " << numPraticantes << std::endl
            << "Tipo de aula: " << std::endl
            << "Instrutor: " << std::endl
            << "Data e hora das aulas: " << dH << std::endl;
}
