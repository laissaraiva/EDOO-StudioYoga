#include "services/Praticante.h"
#include "services/Aula.h"
#include "services/Plano.h"
#include <algorithm>
#include <iostream>

Praticante::Praticante(const std::string &nome, const std::string &cpf,
                       const std::string &genero)
    : Pessoa(nome, cpf, genero), plano(nullptr) {}

Praticante::~Praticante() {
  // Não deletamos o plano aqui pois ele pode ser compartilhado
  // ou gerenciado externamente
  plano = nullptr;

  // Limpa o vetor de aulas (não deleta as aulas, apenas remove as referências)
  aulasInscritas.clear();
}

void Praticante::setPlano(Plano *novoPlano) { plano = novoPlano; }

int Praticante::getId() { return Pessoa::getId(); }

Plano *Praticante::getPlano() const { return plano; }

void Praticante::inscreverEmAula(Aula *aula) {
  if (aula == nullptr) {
    std::cout << "Erro: Aula inválida." << std::endl;
    return;
  }

  // Verifica se já está inscrito nesta aula
  auto it = std::find(aulasInscritas.begin(), aulasInscritas.end(), aula);
  if (it != aulasInscritas.end()) {
    std::cout << "Você já está inscrito nesta aula." << std::endl;
    return;
  }

  aulasInscritas.push_back(aula);
  std::cout << "Inscrição realizada com sucesso!" << std::endl;
}

void Praticante::cancelarInscricao(Aula *aula) {
  if (aula == nullptr) {
    std::cout << "Erro: Aula inválida." << std::endl;
    return;
  }

  auto it = std::find(aulasInscritas.begin(), aulasInscritas.end(), aula);
  if (it != aulasInscritas.end()) {
    aulasInscritas.erase(it);
    std::cout << "Inscrição cancelada com sucesso!" << std::endl;
  } else {
    std::cout << "Você não está inscrito nesta aula." << std::endl;
  }
}

void Praticante::listarAulasInscritas() const {
  if (aulasInscritas.empty()) {
    std::cout << "Nenhuma aula inscrita." << std::endl;
    return;
  }

  std::cout << "\n=== Aulas Inscritas ===" << std::endl;
  for (size_t i = 0; i < aulasInscritas.size(); i++) {
    std::cout << i + 1 << ". ";
    // Assumindo que a classe Aula tem um método para exibir informações
    // Você pode ajustar conforme a implementação da classe Aula
    std::cout << "Aula ID: " << aulasInscritas[i] << std::endl;
  }
}

void Praticante::exibirDetalhes() const {
  std::cout << "\n=== Detalhes do Praticante ===" << std::endl;
  Pessoa::exibirDetalhes(); // Chama o método da classe pai

  if (plano != nullptr) {
    std::cout << "Plano: Ativo" << std::endl;
    // Se a classe Plano tiver um método para exibir detalhes, chame-o aqui
  } else {
    std::cout << "Plano: Nenhum plano ativo" << std::endl;
  }

  std::cout << "Total de aulas inscritas: " << aulasInscritas.size()
            << std::endl;
}
