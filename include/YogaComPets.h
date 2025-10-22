#ifndef YOGACOMPETS_H
#define YOGACOMPETS_H

#include "TipoDeAula.h" // Inclui a classe pai

class YogaComPets : public TipoDeAula {
private:
    std::string regrasPets;

public:
    YogaComPets(const std::string& nome, const std::string& descricao, const std::string& regras);

    std::string getRequisitos() const override;
    void exibirDetalhes() const override;
};

#endif // YOGACOMPETS_H