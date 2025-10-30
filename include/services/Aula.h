#ifndef AULA_H
#define AULA_H

#include <string>
#include <vector>

// Forward declarations para evitar dependências circulares
class Praticante;
class Instrutor;
class TipoDeAula;

class Aula {
private:
  int id;
  int capacidadeMaxima;
  TipoDeAula *tipoDeAula;
  Instrutor *instrutor;
  std::string dataHora;
  std::vector<Praticante *> praticantesInscritos;

public:
  Aula(int id, const std::string &dataHora, int capacidade, TipoDeAula *tipo,
       Instrutor *instr);
  ~Aula(); // Destrutor para gerenciar ponteiros, se necessário

  // --- GETTERS ---
  int getId() const;
  int getCapacidadeMaxima() const;
  int getNumeroDePraticantesInscritos() const;
  TipoDeAula *getTipoDeAula() const;
  Instrutor *getInstrutor() const;
  std::string getDataHora() const;
  const std::vector<Praticante *> &getPraticantesInscritos() const;

  // --- SETTERS ---
  void setCapacidadeMaxima(int capacidade);
  void setTipoDeAula(TipoDeAula *tipo);
  void setInstrutor(Instrutor *instr);
  void setDataHora(const std::string &dataHora);

  // --- REGRAS DE NEGÓCIO ---
  bool adicionarPraticante(Praticante *praticante,
                           class DatabaseManager &dbManager);
  bool removerPraticante(Praticante *praticante,
                         class DatabaseManager &dbManager);
  int verificarVagas() const;
  void listarPraticantesInscritos() const;
  void exibirDetalhesCompletos() const;
};

#endif // AULA_H
