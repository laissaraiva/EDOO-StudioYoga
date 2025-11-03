#include "../include/Instrutor.h" 

#include "../include/Aula.h" 
#include <iostream>

Instrutor::Instrutor(const std::string& nome, 
                     const std::string& cpf, 
                     const std::string& genero, 
                     const std::string& especialidade)
    : Pessoa(nome, cpf, genero), 
      m_especialidade(especialidade) {
    
   
    std::cout << "Instrutor " << getNome() << " criado." << std::endl;
}

Instrutor::~Instrutor() {
    std::cout << "Instrutor " << getNome() << " destruído." << std::endl;
}


void Instrutor::exibirDetalhes() const {
    std::cout << "--- Detalhes do Instrutor ---" << std::endl;
    std::cout << "Nome: " << getNome() << std::endl;   
    std::cout << "CPF: " << getCPF() << std::endl;      
    std::cout << "Gênero: " << getGenero() << std::endl; 
    
    std::cout << "Especialidade: " << m_especialidade << std::endl;
    
    listarAulasMinistradas();
}

void Instrutor::setEspecialidade(const std::string& novaEspecialidade) {
    m_especialidade = novaEspecialidade;
}

std::string Instrutor::getEspecialidade() const {
    return m_especialidade;
}

void Instrutor::adicionarAula(Aula* aula) {
    m_aulasMinistradas.push_back(aula);
}

void Instrutor::listarAulasMinistradas() const {
    std::cout << "Aulas ministradas (" << m_aulasMinistradas.size() << "):" << std::endl;
    
    if (m_aulasMinistradas.empty()) {
        std::cout << "  Nenhuma aula cadastrada para este instrutor." << std::endl;
    } else {
        for (const Aula* aula : m_aulasMinistradas) {
            
            std::cout << "  - Aula ID: " << aula->getId() << std::endl; 
        }
    }
}