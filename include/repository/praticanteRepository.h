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

    /**
     * @brief Insere um novo praticante no banco de dados.
     * @param nome O nome do praticante.
     * @param email O email do praticante.
     * @return O ID do novo praticante inserido, ou 0 em caso de falha.
     */
    int inserirPraticante(const std::string& nome, const std::string& email);

    /**
     * @brief Busca um praticante pelo seu ID.
     * @param id O ID do praticante a ser buscado.
     * @return Um objeto Praticante. (Pode lançar exceção se não encontrar)
     */
    Praticante buscarPraticantePorId(int id);

    /**
     * @brief Lista todos os praticantes no banco de dados.
     * @return Um vetor (lista) de objetos Praticante.
     */
    std::vector<Praticante> listarTodosPraticantes();

    // Você pode adicionar outros métodos CRUD aqui depois:
    // bool atualizarPraticante(int id, const std::string& novoEmail);
    // bool deletarPraticante(int id);
};