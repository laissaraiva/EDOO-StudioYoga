#ifndef PESSOA_H
#define PESSOA_H

#include <string>

class Pessoa {
protected:
    std::string nome;
    std::string cpf;
    std::string genero;
    std::string telefone;

public:
    Pessoa(const std::int& id, const std::string& nome, const std::string& cpf, const std::string& genero, const std::string& telefone)
    : id(id), nome(nome), cpf(cpf), genero(genero), telefone(telefone) {}

    virtual ~Pessoa() = default; // Destrutor virtual para classes base

    // Getters
    std::string getNome() const;
    std::string getCPF() const;
    std::string getGenero() const;
    std::string getTelefone() const;

    // Método virtual puro
    virtual void exibirDetalhes() const = 0;

    // Métodos setters
    void setNome(const std::string& n);
    std::string getNome() const;

    void setCpf(const std::string& c);
    std::string getCpf() const;

    void setGenero(const std::string& g);
    std::string getGenero() const;

    void setTelefone(const std::string& t);
    std::string getTelefone() const;

};

#endif // PESSOA_H