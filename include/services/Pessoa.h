#ifndef PESSOA_H
#define PESSOA_H

#include <string>

// Classe abstrata Pessoa
class Pessoa {
private:
    int id;
    std::string nome;
    std::string cpf;
    std::string genero;

public:
    Pessoa(int id, const std::string& nome, const std::string& cpf, const std::string& genero);
    virtual ~Pessoa();

    // GETTERS
    int getId() const;
    std::string getNome() const;
    std::string getCPF() const;
    std::string getGenero() const;

    // SETTERS
    void setNome(const std::string& novoNome);
    void setCPF(const std::string& novoCPF);
    void setGenero(const std::string& novoGenero);

    // MÉTODO VIRTUAL
    virtual void exibirDetalhes() const = 0;
};

#endif // PESSOA_H