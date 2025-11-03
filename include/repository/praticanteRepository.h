#pragma once

#include "sqlite3.h"
#include <string>
#include <vector>
#include "services/Praticante.h" 

class PraticanteRepository {
private:
    sqlite3* db; 

public:
    PraticanteRepository(sqlite3* dbHandle);

    int inserirPraticante(const std::string& nome, const std::string& email);

    Praticante buscarPraticantePorId(int id);

    std::vector<Praticante> listarTodosPraticantes();
};