#ifndef PESSOA_H
#define PESSOA_H

#include <string>

class Pessoa {
protected:
    std::string nome;
    std::string cpf;
    std::string genero;

public:
    Pessoa(const std::string& nome, const std::string& cpf, const std::string& genero);
    virtual ~Pessoa() {} // Destrutor virtual para classes base

    // Getters
    std::string getNome() const;
    std::string getCPF() const;
    std::string getGenero() const;

    // Método virtual puro
    virtual void exibirDetalhes() const = 0;
};

#endif // PESSOA_H