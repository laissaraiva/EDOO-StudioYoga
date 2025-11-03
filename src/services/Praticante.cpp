#include "services/Praticante.h"
#include "services/Aula.h"
#include "services/Plano.h"
#include <algorithm>
#include <iostream>

Praticante::Praticante(int id, const std::string &nome, const std::string &cpf, const std::string &genero, Plano *plano)
    : Pessoa(id, nome, cpf, genero), plano(plano) {}

Praticante::~Praticante() {
    // Não deletar plano (não é owner), mas pode limpar aulasInscritas
    aulasInscritas.clear();
}

// GETTERS
Plano *Praticante::getPlano() const {
    return this->plano;
}

const std::vector<Aula *> &Praticante::getAulasInscritas() const {
    return this->aulasInscritas;
}

// SETTERS
void Praticante::setPlano(Plano *novoPlano) {
    if (novoPlano == nullptr) {
        std::cerr << "[ERRO] O plano não pode ser nulo." << std::endl;
        return;
    }
    this->plano = novoPlano;
}

// REGRAS DE NEGÓCIO
bool Praticante::inscreverEmAula(Aula *aula) {
    if (aula == nullptr) {
        std::cerr << "[ERRO] Aula nula ao tentar inscrição." << std::endl;
        return false;
    }
    // Verifica se já está inscrito
    auto it = std::find(aulasInscritas.begin(), aulasInscritas.end(), aula);
    if (it != aulasInscritas.end()) {
        std::cerr << "[ERRO] Praticante já está inscrito nesta aula." << std::endl;
        return false;
    }
    aulasInscritas.push_back(aula);
    return true;
}

bool Praticante::cancelarInscricao(Aula *aula) {
    if (aula == nullptr) {
        std::cerr << "[ERRO] Aula nula ao tentar cancelar inscrição." << std::endl;
        return false;
    }
    auto it = std::find(aulasInscritas.begin(), aulasInscritas.end(), aula);
    if (it == aulasInscritas.end()) {
        std::cerr << "[ERRO] Praticante não está inscrito nesta aula." << std::endl;
        return false;
    }
    aulasInscritas.erase(it);
    return true;
}

void Praticante::listarAulasInscritas() const {
    std::cout << --AULAS INSCRITA--" << std::endl;
    for (const auto &aula : aulasInscritas) {
        if (aula) {
            std::cout << "Aula ID: " << aula->getId() << std::endl;
            // Pode adicionar mais detalhes se necessário
        }
    }
}

void Praticante::exibirDetalhes() const {
    std::cout << --DETALHES DO PRATICANT--" << std::endl
              << "Id: " << getId() << std::endl
              << "Nome: " << getNome() << std::endl
              << "CPF: " << getCPF() << std::endl
              << "Gênero: " << getGenero() << std::endl;
    if (plano) {
        // Supondo que Plano tem getNome()
        std::cout << "Plano: " << plano << std::endl;
    } else {
        std::cout << "Plano: (nenhum)" << std::endl;
    }
    std::cout << "Quantidade de aulas inscritas: " << aulasInscritas.size() << std::endl;
}
