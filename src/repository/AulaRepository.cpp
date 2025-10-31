#include "repository/AulaRepository.h"

#include <iostream>
#include <string>
#include "services/Aula.h"
#include "services/Instrutor.h"
#include "services/TipoDeAula.h"

AulaRepository::AulaRepository(sqlite3 *dbHandle) : db(dbHandle)
{
    if (this->db == nullptr)
    {
        std::cerr << "[ERRO FATAL] AulaRepository foi criado com um ponteiro de banco de dados nulo!" << std::endl;
    }
}

// --- CRUD Operations ---
// --- CREATE ---

int AulaRepository::agendarAula(const std::string &dataHora, int capacidade,  int instrutorId,  int tipoAulaId)
{
    
    // Valida por precaução se o banco de dados continua válido
    if (this->db == nullptr)
        return -1;

    // Criamos o template com o comando sql que iremos utilizar para inserir os dados
    const char *sql = "INSERT INTO Aula (dataHora, capacidadeMaxima, instrutor_id, tipo_aula_id) "
                      "VALUES (?, ?, ?, ?);";

    sqlite3_stmt *stmt = nullptr; // Variável que vai receber o template sql pós compilado

    // Compila o template sql
    if (sqlite3_prepare_v2(this->db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "[ERRO DB] ao preparar 'agendarAula': " << sqlite3_errmsg(this->db) << std::endl;
        return -1;
    }

    // Liga as variáveis c++ aos placeholders do template ( os "?" que estão no template)
    sqlite3_bind_text(stmt, 1, dataHora.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, capacidade);
    sqlite3_bind_int(stmt, 3, instrutorId);
    sqlite3_bind_int(stmt, 4, tipoAulaId);

    // Executa o comando
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr
            << "[ERRO DB] ao executar 'agendarAula': " << sqlite3_errmsg(this->db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    // Pega o id gerado pelo banco de dados
    int novoId = sqlite3_last_insert_rowid(this->db);

    // Libera a variável que criamos para armazenar o template sql pós compilado
    sqlite3_finalize(stmt);

    std::cout << "[DB] Aula agendada com sucesso. Novo ID: " << novoId << std::endl;

    return novoId;
}

bool AulaRepository::inscreverPraticanteEmAula(int praticanteId, int aulaId)
{
    if (this->db == nullptr)
        return false; // Mesma validação de segurança que fizemos no método anterior

    // 1. Template sql para inserir na tabela participa
    const char *sql = "INSERT OR IGNORE INTO Participa (praticante_id, aula_id) VALUES (?, ?);";

    sqlite3_stmt *stmt = nullptr; // Variável que vai receber o template sql pós compilado

    // 2. PREPARE
    if (sqlite3_prepare_v2(this->db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "[ERRO DB] ao preparar 'inscreverPraticante': " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }

    // 3. BIND
    sqlite3_bind_int(stmt, 1, praticanteId);
    sqlite3_bind_int(stmt, 2, aulaId);

    // 4. STEP
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr
            << "[ERRO DB] ao executar 'inscreverPraticante': " << sqlite3_errmsg(this->db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // 5. FINALIZE
    sqlite3_finalize(stmt);

    // Verificação para ver se alguma linha foi realmente mudada, para verificar se a inscrição é realmente nova.
    int changes = sqlite3_changes(this->db);
    if (changes > 0)
    {
        std::cout << "[DB] Praticante " << praticanteId << " inscrito na aula" << std::endl;
    }
    else
    {
        std::cout << "[DB] Praticante " << praticanteId << " já estava inscrito na aula " << aulaId << "." << std::endl;
    }

    return true;
}

/*
Estamos utilizando ao mexer com banco de dados uma abordagem que é chamada prepare -> bind -> step -> finalize para garantir eficiência e segurança nos acessos ao banco de dados.

1. Prepare ( que utiliza o método sqlite3_prepare_v2)

Basicamente vai pegar o nosso template de sql, vai pré compilar, validando a sintaxe se as tabelas existem e etc e gera um sqlite3_stmt* que é o plano de execução pré-compilado

2. Bind ( que utiliza o método sqlite3_bind_*)

Basicamente vai pegar esse statement que foi gerado no passo anterior e vai atribuir as variáveis que queremos nos placeholders que existem no template ( nesse caso são os "?")

3. Step ( usa o método sqlite3_step)

É aqui que o filho chora e a mãe não vê, como já temos nosso comando sql pronto, ele coloca o sqlite para executar, ai é onde realmente fazemos a query.

4. Finalize ( sqlite3_finalize)

Serve somente para liberar o ponteiro do sqlite3_stmt* que utilizamos previamente e não gerar vazamento de memória.
*/