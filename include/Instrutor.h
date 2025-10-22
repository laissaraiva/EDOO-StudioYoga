#ifndef INSTRUTOR_H
#define INSTRUTOR_H

#include "Pessoa.h" // Inclui a classe pai
#include <string>

class Instrutor : public Pessoa {
private:
    std::string especialidade;

public:
    Instrutor(const std::string& nome, const std::string& cpf, const std::string& genero, const std::string& especialidade);

    void setEspecialidade(const std::string& novaEspecialidade);
    std::string getEspecialidade() const;

    void exibirDetalhes() const override;
};

#endif // INSTRUTOR_H