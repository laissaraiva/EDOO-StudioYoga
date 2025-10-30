#include "services/Aula.h"
#include "repository/databaseManager.h" // Para saber o que é DatabaseManager
#include "services/Praticante.h"        // Para poder chamar praticante->getId()
#include <iostream>

class Praticante;

bool Aula::adicionarPraticante(Praticante *praticante,
                               DatabaseManager &dbManager) {
  return true;
}
