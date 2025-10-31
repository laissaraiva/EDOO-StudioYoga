#include "sqlite3.h"
#include <string>

class AulaRepository
{
private:
  sqlite3 *db;

public:
  AulaRepository(sqlite3 *dbHandle);

  // --- CRUD Operations ---

  // --- CREATE ---

  int agendarAula(const std::string &dataHora, int capacidade,
                  int instrutorId, int tipoAulaId);

  bool inscreverPraticanteEmAula(int praticanteId, int aulaID);
};
