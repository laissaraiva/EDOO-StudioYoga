#include "repository/PraticanteRepository.h"
#include <iostream>   // Para std::cerr (logs de erro)
#include <stdexcept>  // Para std::runtime_error

// Implementação do Construtor
PraticanteRepository::PraticanteRepository(sqlite3* dbHandle) : db(dbHandle) {
    if (this->db == nullptr) {
        throw std::runtime_error("O 'handle' do banco de dados (db) não pode ser nulo.");
    }
}

// Implementação do INSERT (Receita de Bolo)
int PraticanteRepository::inserirPraticante(const std::string& nome, const std::string& email) {
    
    // 1. Template SQL
    const char* sql = "INSERT INTO Praticantes (Nome, Email) VALUES (?, ?);";
    sqlite3_stmt* stmt = nullptr;
    
    // 2. PREPARE
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar statement (INSERT Praticante): " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // Limpa o statement em caso de erro no prepare
        return 0; // Retorna 0 para indicar falha
    }

    // 3. BIND (Ligar as variáveis)
    sqlite3_bind_text(stmt, 1, nome.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);

    // 4. STEP (Executar)
    int novoId = 0;
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        // Pega o ID da linha que acabou de ser inserida
        novoId = sqlite3_last_insert_rowid(db);
    } else {
        std::cerr << "Erro ao executar statement (INSERT Praticante): " << sqlite3_errmsg(db) << std::endl;
    }

    // 5. FINALIZE (Limpar)
    sqlite3_finalize(stmt);
    return novoId; // Retorna o ID do novo praticante (ou 0 se falhou)
}


// Implementação do SELECT (para listar todos)
std::vector<Praticante> PraticanteRepository::listarTodosPraticantes() {
    std::vector<Praticante> praticantes;
    
    // 1. Template SQL
    const char* sql = "SELECT ID, Nome, Email FROM Praticantes;";
    sqlite3_stmt* stmt = nullptr;

    // 2. PREPARE
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar statement (SELECT Praticantes): " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return praticantes; // Retorna lista vazia
    }

    // 3. BIND (Não precisa)

    // 4. STEP (em loop 'while' para ler cada linha)
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Pegar os dados da linha (índice da coluna começa em 0)
        int id = sqlite3_column_int(stmt, 0);
        
        const unsigned char* nomeBytes = sqlite3_column_text(stmt, 1);
        std::string nome = reinterpret_cast<const char*>(nomeBytes);
        
        const unsigned char* emailBytes = sqlite3_column_text(stmt, 2);
        std::string email = reinterpret_cast<const char*>(emailBytes);

        // Criar o objeto de Serviço (Camada 1) e adicionar na lista
        praticantes.emplace_back(id, nome, email);
    }

    // 5. FINALIZE
    sqlite3_finalize(stmt);
    return praticantes;
}


// Implementação do SELECT (para buscar por ID)
Praticante Praticante::buscarPraticantePorId(int id) {
    // 1. Template SQL
    const char* sql = "SELECT ID, Nome, Email FROM Praticantes WHERE ID = ?;";
    sqlite3_stmt* stmt = nullptr;

    // 2. PREPARE
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar statement (SELECT Praticante por ID): " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        throw std::runtime_error("Erro de banco de dados ao buscar praticante.");
    }

    // 3. BIND
    sqlite3_bind_int(stmt, 1, id); // Liga o ID ao primeiro '?'

    // 4. STEP (só esperamos um resultado, então usamos 'if' em vez de 'while')
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Pegar os dados da linha
        int idEncontrado = sqlite3_column_int(stmt, 0);
        const unsigned char* nomeBytes = sqlite3_column_text(stmt, 1);
        std::string nome = reinterpret_cast<const char*>(nomeBytes);
        const unsigned char* emailBytes = sqlite3_column_text(stmt, 2);
        std::string email = reinterpret_cast<const char*>(emailBytes);

        // Criar o objeto e finalizar
        Praticante p(idEncontrado, nome, email);
        sqlite3_finalize(stmt);
        return p;

    } else {
        // Não encontrou (ou deu erro)
        sqlite3_finalize(stmt);
        throw std::runtime_error("Praticante com o ID especificado não foi encontrado.");
    }
}