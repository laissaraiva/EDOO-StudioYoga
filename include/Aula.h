#ifndef AULA_H
#define AULA_H

#include <string>
#include <vector>

// Forward declarations para evitar dependências circulares
class Praticante;
class Instrutor;
class TipoDeAula;

class Aula {
private:
    int id;
    std::string dataHora;
    int capacidadeMaxima;
    TipoDeAula* tipoDeAula;
    Instrutor* instrutor;
    std::vector<Praticante*> praticantesInscritos;

public:
    Aula(int id, const std::string& dataHora, int capacidade, TipoDeAula* tipo, Instrutor* instr);
    ~Aula(); // Destrutor para gerenciar ponteiros, se necessário

    bool adicionarPraticante(Praticante* praticante);
    bool removerPraticante(Praticante* praticante);
    int verificarVagas() const;

    void listarPraticantesInscritos() const;
    void exibirDetalhesCompletos() const;
    int getId() const;
};

#endif // AULA_H