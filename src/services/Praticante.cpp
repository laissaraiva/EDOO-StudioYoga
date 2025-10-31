#include "services/Praticante.h"
#include "services/Aula.h"
#include "services/Plano.h"
#include <algorithm>
#include <iostream>

int Praticante::getId()
{
    return this->Id;
}

Plano *Praticante::getPlano() const
{
    return this->plano;
}
