#ifndef HOTYOGA_H
#define HOTYOGA_H

#include "TipoDeAula.h" // Inclui a classe pai

class HotYoga : public TipoDeAula {
private:
    int temperaturaSala;

public:
    HotYoga(const std::string& nome, const std::string& descricao, int temperatura);

    std::string getRequisitos() const override;
    void exibirDetalhes() const override;
};

#endif // HOTYOGA_H