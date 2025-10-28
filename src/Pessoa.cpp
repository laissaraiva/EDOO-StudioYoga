#include "../include/Pessoa.h"

std::string Pessoa::getNome() const {
    return nome;
}

std::string Pessoa::getCPF() const {
    return cpf;
}

std::string Pessoa::getGenero() const {
    return genero;
}

std::string Pessoa::getTelefone() const {
    return telefone;
}

void Pessoa::setNome(const std::string& n) {
    nome = n;
}

void Pessoa::setCpf(const std::string& c) {
    cpf = c;
}

void Pessoa::setGenero(const std::string& g) {
    genero = g;
}

void Pessoa::setTelefone(const std::string& t) {
    telefone = t;
}