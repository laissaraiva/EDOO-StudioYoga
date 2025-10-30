
#include "Plano.h"

// Implementação do Construtor
Plano::Plano(int id, const std::string& tipo, float valor)
    : id(id), tipo(tipo), valor(valor) {
    
}
// getters da classe
int Plano::getId() const {
    return this->id;
}

std::string Plano::getTipo() const {
    return this->tipo;
}

float Plano::getValor() const {
    return this->valor;
}