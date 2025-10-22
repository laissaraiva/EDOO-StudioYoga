#ifndef TIPODEAULA_H
#define TIPODEAULA_H

#include <string>

class TipoDeAula {
protected:
    std::string nome;
    std::string descricao;

public:
    TipoDeAula(const std::string& nome, const std::string& descricao);
    virtual ~TipoDeAula() {}

    std::string getNome() const;

    virtual std::string getRequisitos() const = 0;
    virtual void exibirDetalhes() const = 0;
};

#endif // TIPODEAULA_H