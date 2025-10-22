#ifndef PRATICANTE_H
#define PRATICANTE_H

#include "Pessoa.h" // Inclui a classe pai
#include <vector>

// Forward declarations
class Plano;
class Aula;

class Praticante : public Pessoa {
private:
    Plano* plano;
    std::vector<Aula*> aulasInscritas;

public:
    Praticante(const std::string& nome, const std::string& cpf, const std::string& genero);
    ~Praticante(); // Destrutor para gerenciar o ponteiro do plano

    void setPlano(Plano* novoPlano);
    Plano* getPlano() const;

    void inscreverEmAula(Aula* aula);
    void cancelarInscricao(Aula* aula);
    void listarAulasInscritas() const;

    void exibirDetalhes() const override;
};

#endif // PRATICANTE_H