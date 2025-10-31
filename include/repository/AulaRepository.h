#include "sqlite3.h"

class AulaRepository {
private:
  sqlite3 *db;

public:
  AulaRepository(sqlite3 *dbHandle);

  // --- CRUD Operations ---

  // --- CREATE ---

  Aula *agendarAula(const std::string &dataHora, int capacidade,
                    int tipoDeAulaId, int instrutorId);

  bool inscreverPraticanteEmAula(int praticanteId, int aulaID);
}
