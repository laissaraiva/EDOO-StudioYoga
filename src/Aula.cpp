#include "Aula.h"
#include <iostream>
#include <vector>

class TipoDeAula;
class Instrutor;
class Praticante;

Aula::Aula(int id, const std::string &dataHora, int capacidadeMaxima,
           TipoDeAula *tipoDeAula, Instrutor *instrutor)
    : id(id), dataHora(dataHora), capacidadeMaxima(capacidadeMaxima), tipoDeAula(tipoDeAula),
      instrutor(instrutor) {}

bool Aula::adicionarPraticante(Praticante *praticante) {}
