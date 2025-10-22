#ifndef PLANO_H
#define PLANO_H

#include <string>

class Plano {
private:
    int id;
    std::string tipo;
    float valor;

public:
    Plano(int id, const std::string& tipo, float valor);

    int getId() const;
    std::string getTipo() const;
    float getValor() const;
};

#endif // PLANO_H