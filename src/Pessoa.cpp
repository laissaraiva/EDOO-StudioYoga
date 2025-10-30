#include "Pessoa.h"

Pessoa::Pessoa(const std::string& nome, const std::string& cpf, const std::string& genero)
    : nome(nome), cpf(cpf), genero(genero) {
}

std::string Pessoa::getNome() const {
    return nome;
}

std::string Pessoa::getCPF() const {
    return cpf;
}

std::string Pessoa::getGenero() const {
    return genero;
}

int Pessoa::getId() const {
    // Implementação básica - pode ser ajustada conforme necessário
    // Você pode querer adicionar um atributo id na classe
    return 0;
}
