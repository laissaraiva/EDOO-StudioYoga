-----

# Documentação de Bordo: Projeto Studio de Yoga

## 1\. Visão Geral do Projeto

**Objetivo:** Construir um sistema de informação para um Studio de Yoga, como projeto da disciplina de EDOO.

**Requisitos Principais:**

  * **Código:** C++.
  * **Conceitos:** Deve usar POO (Classes, Herança, Polimorfismo, Encapsulamento).
  * **Funcionalidade:** Implementar um **CRUD** (Create, Read, Update, Delete).
  * **Persistência:** Conectar a um **Banco de Dados**.

## 2\. A Arquitetura: SOLID e Separação de Camadas

Para cumprir os requisitos e manter o projeto organizado, escolhemos uma arquitetura que segue o **Princípio da Responsabilidade Única (SOLID)**.

Nós **NÃO** misturamos a lógica de negócio com a lógica de banco de dados na mesma classe. Em vez disso, o projeto é dividido em **três camadas** (representadas pelas pastas):

### Camada 1: `services/` (A Lógica de Negócios)

  * **O que é?** São as nossas classes de modelo (POO), como `Aula`, `Praticante`, `Instrutor`, etc.
  * **Responsabilidade:** Cuidar **APENAS** das regras de negócio e da lógica de memória.
  * **Exemplo:** A classe `Aula` sabe checar se uma aula está lotada (olhando seu `std::vector`), mas ela **NÃO FAZ IDEIA** de que um banco de dados existe.
  * **Arquivos:** `include/services/SuaClasse.h` e `src/services/SuaClasse.cpp`.

### Camada 2: `repository/` (A Lógica de Persistência / CRUD)

  * **O que é?** São classes "CRUD" dedicadas, uma para cada classe de serviço. (Ex: `AulaRepository`, `PraticanteRepository`).
  * **Responsabilidade:** Cuidar **APENAS** de "falar" com o banco de dados. É aqui que moram os comandos SQL (`INSERT`, `SELECT`, `UPDATE`, `DELETE`).
  * **Exemplo:** `AulaRepository` tem o método `agendarAula` que executa um `INSERT INTO Aula...`.
  * **Arquivos:** `include/repository/SuaClasseRepository.h` e `src/repository/SuaClasseRepository.cpp`.

### Camada 3: `main.cpp` (O Orquestrador / UI)

  * **O que é?** O ponto de entrada do programa, que serve como nossa Interface de Usuário (UI).
  * **Responsabilidade:** Orquestrar o fluxo. Ele exibe o menu, coleta dados do usuário, e chama as outras duas camadas na ordem correta.
  * **Exemplo de Fluxo:**
    1.  O `main` pede os dados da nova aula.
    2.  Ele chama `repoAula->agendarAula(...)` (Camada 2) para salvar no banco.
    3.  O repositório retorna o ID da nova aula.
    4.  O `main` usa esse ID para criar o objeto `Aula` (Camada 1) em memória.

## 3\. O Banco de Dados (SQLite)

  * **Tecnologia:** Escolhemos **SQLite** por sua simplicidade. O banco de dados inteiro é um único arquivo (`yoga_studio.db`) que é criado na pasta `build/`.
  * **Integração:** Usamos o método de **Amalgamação**. Os arquivos `sqlite3.c` e `sqlite3.h` estão compilados diretamente no nosso projeto.
  * **Schema:** A "planta" do nosso banco de dados está em `database/schema.sql`. Ele define todas as tabelas, colunas e chaves estrangeiras.
  * **Conexão:** A classe `DatabaseManager` (`repository/databaseManager.h`) é a **única** responsável por abrir (`abrirConexao`) e fechar a conexão. Ela também inicializa as tabelas (`inicializarTabelas`) lendo o `schema.sql`.

## 4\. Como Compilar e Rodar

O projeto usa **CMake** para gerenciar a compilação.

  * **Arquivo de Configuração:** `CMakeLists.txt` (já está configurado para as pastas `services/` e `repository/`).

**Para compilar (do zero):**

1.  Estando na raiz do projeto, crie e entre na pasta `build`:
    ```bash
    rm -rf build   # (Opcional: limpa o build antigo)
    mkdir build
    cd build
    ```
2.  Rode o CMake para gerar os arquivos de build:
    ```bash
    cmake ..
    ```
3.  Compile o projeto:
    ```bash
    cmake --build .
    ```
4.  Execute o programa (de dentro da pasta `build/`):
    ```bash
    ./Studio-Yoga
    ```
    *(Nota: Como o `main.cpp` está configurado para rodar de dentro da raiz, talvez seja necessário executar `./Studio-Yoga` de lá, ou ajustar o caminho do `schema.sql` para `../database/schema.sql` se rodar do `build/`.)*

-----

## 5\. GUIA PARA O TIME: Como Implementar as Classes Faltando

Este é o seu "passo a passo" para adicionar uma nova entidade (ex: `Praticante` ou `Instrutor`).

### Passo 1: Implementar a Classe de Serviço (Lógica de Negócios)

1.  **Arquivos:** Crie (se não existir) `include/services/SuaClasse.h` e `src/services/SuaClasse.cpp`.
2.  **No `.h` (ex: `Praticante.h`):**
      * Defina os atributos como `private` ou `protected`.
      * Crie o construtor (que define o `id`).
      * Crie os **Getters** públicos (ex: `int getId() const;`).
      * Crie os **Setters** públicos (ex: `void setEmail(const std.string& novoEmail);`).
      * **NÃO** inclua nada de SQLite ou Repositório aqui.
3.  **No `.cpp` (ex: `Praticante.cpp`):**
      * Implemente o construtor, getters e setters.
      * **IMPORTANTE:** Coloque sua **lógica de validação** (regras de negócio) dentro dos **Setters**.
      * *Veja `src/services/Aula.cpp` como exemplo de implementação.*

### Passo 2: Implementar a Classe de Repositório (Lógica do CRUD)

1.  **Arquivos:** Crie `include/repository/SuaClasseRepository.h` e `src/repository/SuaClasseRepository.cpp`.
2.  **No `.h`:**
      * Inclua `sqlite3.h`.
      * Tenha um atributo `private: sqlite3* db;`.
      * Tenha um construtor: `SuaClasseRepository(sqlite3* dbHandle);`.
      * Declare os métodos CRUD (ex: `bool inserirPraticante(...)`, `void listarPraticantes()`).
3.  **No `.cpp` (A "Receita do CRUD"):**
      * Implemente o construtor: `SuaClasseRepository::SuaClasseRepository(sqlite3* dbHandle) : db(dbHandle) {}`
      * Para `INSERT`, `UPDATE`, `DELETE`, use a "Receita de Bolo" do SQLite:
          * *Veja `src/repository/AulaRepository.cpp` (método `agendarAula`) como exemplo perfeito.*
        <!-- end list -->
        ```cpp
        // 1. O Template SQL
        const char* sql = "INSERT INTO SuaTabela (col1, col2) VALUES (?, ?);";
        sqlite3_stmt* stmt = nullptr;

        // 2. PREPARE
        if (sqlite3_prepare_v2(this->db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            // ... tratar erro ...
        }

        // 3. BIND (Ligar as variáveis)
        sqlite3_bind_text(stmt, 1, varString.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, varInt);

        // 4. STEP (Executar)
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            // ... tratar erro ...
        }

        // (Opcional: pegar o novo ID)
        // int novoId = sqlite3_last_insert_rowid(this->db);

        // 5. FINALIZE (Limpar)
        sqlite3_finalize(stmt);
        return true; // ou o novoId
        ```
      * Para `SELECT`, o ritual é parecido, mas o `step` é feito em um loop `while`:
        ```cpp
        const char* sql = "SELECT id, nome FROM SuaTabela WHERE col = ?;";
        // ... (prepare) ...
        // ... (bind) ...

        // Loop 'step' para ler cada linha de resultado
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // Pegar os dados da linha (índice da coluna começa em 0)
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* nome_bytes = sqlite3_column_text(stmt, 1);
            std::string nome = reinterpret_cast<const char*>(nome_bytes);

            // ... (fazer algo com os dados: imprimir ou criar um objeto) ...
        }

        // ... (finalize) ...
        ```

### Passo 3: Atualizar o `CMakeLists.txt`

1.  Abra o arquivo `CMakeLists.txt`.
2.  Adicione os seus **novos arquivos `.cpp`** nas seções corretas:
    ```cmake
    add_executable(Studio-Yoga
        # ...
        # Adicione o service
        src/services/SuaClasse.cpp
        
        # ...
        
        # Adicione o repository
        src/repository/SuaClasseRepository.cpp
    )
    ```
3.  Salve o arquivo.

### Passo 4: Conectar no `main.cpp`

1.  No `main.cpp`, inclua seu novo repositório:
    `#include "repository/SuaClasseRepository.h"`
2.  Instancie o repositório após o `DatabaseManager`:
    `SuaClasseRepository repoSuaClasse(dbManager.getDBHandle());`
3.  Chame os métodos do repositório no seu menu `switch/case`:
    ```cpp
    case 1: // Cadastrar
        // ... (pedir nome, email, etc. do usuário) ...
        repoSuaClasse.inserirPraticante(nome, email, ...);
        break;
    case 2: // Listar
        repoSuaClasse.listarPraticantes();
        break;
    ```

## 6\. Status Atual (Checkpoint 31/10)

  * **Fundação Pronta:** Build (`CMakeLists.txt`), Conexão (`DatabaseManager`) e Schema (`schema.sql`) estão 100% funcionais.
  * **Implementação Feita:**
      * `Aula` (Serviço): Lógica de negócios implementada.
      * `AulaRepository`: Métodos de `INSERT` (`agendarAula`, `inscreverPraticanteEmAula`) implementados e testados.
  * **O que falta implementar (Tarefas da Equipe):**
      * `Praticante` (Serviço + Repositório)
      * `Instrutor` (Serviço + Repositório)
      * `Plano` (Serviço + Repositório)
      * `TipoDeAula` e suas filhas (Serviço + Repositório)
      * `main.cpp` (A UI final com o menu)
      * Entregáveis Finais (Relatório, Vídeo, etc.)

-----
