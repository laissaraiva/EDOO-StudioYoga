#include "services/Aula.h"
#include "sqlite3.h"

class AulaRepository
{
private:
  sqlite3 *db;

public:
  AulaRepository(sqlite3 *dbHandle);

  // --- CRUD Operations ---

  // --- CREATE ---

  int agendarAula(const std::string &dataHora, int capacidade, int tipoDeAulaId,
                  int instrutorId);

  bool inscreverPraticanteEmAula(int praticanteId, int aulaID);

  // --- READ ---
  void listarAulas();
  void listarAulaPorId(int aulaId);

  // --- UPDATE ---
  bool atualizarAula(int aulaId, int novaCapacidade);
  // --- DELETE ---
  bool deletarAula(int aulaId);
};
