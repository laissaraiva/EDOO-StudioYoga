#include "services/Pessoa.h"
#include <iostream>

Pessoa::Pessoa(int id, const std::string &nome, const std::string &cpf, const std::string &genero)
  : id(id), nome(nome), cpf(cpf), genero(genero) {}

Pessoa::~Pessoa() {}

// GETTERS
int Pessoa::getId() const { return this->id; }

std::string Pessoa::getNome() const { return this->nome; }

std::string Pessoa::getCPF() const { return this->cpf; }

std::string Pessoa::getGenero() const { return this->genero; }

// SETTERS
void Pessoa::setNome(const std::string &nome) {
  if (nome.empty()) {
    std::cerr << "[ERRO] O nome não pode ser vazio." << std::endl;
    return;
  }
  this->nome = nome;
}

void Pessoa::setCPF(const std::string &cpf) {
  if (cpf.empty()) {
    std::cerr << "[ERRO] O CPF não pode ser vazio." << std::endl;
    return;
  }
  // Validação simples se CPF tem 11 dígitos numéricos
  if (cpf.length() != 11 || !std::all_of(cpf.begin(), cpf.end(), ::isdigit)) {
    std::cerr << "[ERRO] Formato de CPF inválido. Deve conter 11 dígitos numéricos." << std::endl;
    return;
  }
  this->cpf = cpf;
}

void Pessoa::setGenero(const std::string &genero) {
  if (genero.empty()) {
    std::cerr << "[ERRO] O gênero não pode ser vazio." << std::endl;
    return;
  }
  this->genero = genero;
}

