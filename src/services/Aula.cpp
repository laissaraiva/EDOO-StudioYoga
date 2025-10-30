#include "services/Aula.h"
#include "repository/databaseManager.h" // Para saber o que é DatabaseManager
#include "services/Praticante.h"        // Para poder chamar praticante->getId()
#include <iostream>

class Praticante;

bool Aula::adicionarPraticante(Praticante *praticante,
                               DatabaseManager &dbManager) {

  // 1. Lógica de Negócios (C++)
  if (this->praticantesInscritos.size() >= this->capacidadeMaxima) {
    std::cout << "Aula lotada!" << std::endl;
    return false;
  }

  // (Você também pode querer verificar se o praticante já está na lista)

  // 2. Atualiza o objeto C++
  this->praticantesInscritos.push_back(praticante);

  // 3. Atualiza o Banco de Dados (chamando nosso novo método)
  // (Assumindo que suas classes têm getters para os IDs)
  int pId = praticante->getId();
  int aId = this->getId();

  if (!dbManager.inserirInscricao(pId, aId)) {
    // Se o DB falhar, talvez você queira reverter a
    // inserção no vetor (lógica de "rollback")
    this->praticantesInscritos
        .pop_back(); // Remove o praticante que falhou no DB
    return false;
  }

  return true;
}
