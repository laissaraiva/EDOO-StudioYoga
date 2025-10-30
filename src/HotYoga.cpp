
#include "HotYoga.h"
#include <iostream>  
#include <sstream>  

// Implementação do Construtor
HotYoga::HotYoga(const std::string& nome, const std::string& descricao, int temperatura)
    : TipoDeAula(nome, descricao), temperaturaSala(temperatura) {
    // O corpo do construtor pode ficar vazio, pois toda a inicialização
    // foi feita na "lista de inicialização de membros" acima.
}

//Implementação do método getRequisitos
std::string HotYoga::getRequisitos() const {
    // Usamos stringstream para construir a string de forma limpa,
    // misturando texto com a variável 'temperaturaSala'.
    std::stringstream ss;
    ss << "Sala aquecida! Trazer garrafa de água e toalha. Temperatura: "
       << this->temperaturaSala << "°C.";
    
   
    return ss.str();
}

//Implementação do método exibirDetalhes()
void HotYoga::exibirDetalhes() const {
    // Imprime os detalhes no console.
    // uso de protect para acessar os atributos herdados da classe base.
    std::cout << "--- " << this->nome << " (Hot Yoga) ---" << std::endl;
    std::cout << "Descrição: " << this->descricao << std::endl;
    std::cout << "Temperatura da Sala: " << this->temperaturaSala << "°C" << std::endl;
    
    //reutilização  do método getRequisitos() criado
    std::cout << "Requisitos: " << this->getRequisitos() << std::endl;
}