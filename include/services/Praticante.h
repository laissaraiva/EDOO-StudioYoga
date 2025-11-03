#ifndef PRATICANTE_H
#define PRATICANTE_H

#include <string>
#include <vector>
#include "Pessoa.h" // Herda

// Forward declarations para evitar dependências circulares
class Plano;
class Aula;

class Praticante : public Pessoa {
private:
    Plano *plano; // Acoplamento explícito
    std::vector<Aula *> aulasInscritas;

public:
    Praticante(int id, const std::string &nome, const std::string &cpf, const std::string &genero, Plano *plano = nullptr);
    ~Praticante();

    // GETTERS
    Plano *getPlano() const;
    const std::vector<Aula *> &getAulasInscritas() const;

    // SETTERS
    void setPlano(Plano *novoPlano);

    // REGRAS DE NEGÓCIO
    bool inscreverEmAula(Aula *aula);
    bool cancelarInscricao(Aula *aula);
    void listarAulasInscritas() const;
    void exibirDetalhes() const override;
};

#endif // PRATICANTE_H