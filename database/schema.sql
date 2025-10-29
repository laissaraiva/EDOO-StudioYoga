PRAGMA foreign_keys = ON ;

CREATE TABLE IF NOT EXISTS Plano (
id INTEGER PRIMARY KEY AUTOINCREMENT,
nome TEXT NOT NULL,
preco REAL NOT NULL,

);

CREATE TABLE IF NOT EXISTS TipoDeAula (
id INTEGER PRIMARY KEY AUTOINCREMENT,
  nome TEXT NOT NULL UNIQUE,
  descricao TEXT,

  -- Atributos específicos das classes filhas
  temperaturaSala INTEGER,
  regrasPets TEXT
);

CREATE TABLE IF NOT EXISTS Praticante (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  nome TEXT NOT NULL,
  email TEXT NOT NULL UNIQUE,

  -- Atributo específico de chave estrangeira. Relacionamento 1-N Praticante - Aula
  plano_id INTEGER,
  FOREIGN KEY (plano_id) REFERENCES Plano(id)
);

CREATE TABLE IF NOT EXISTS Instrutor (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  nome TEXT NOT NULL,
  email TEXT NOT NULL UNIQUE,
  especialidade TEXT NOT NULL
);

  CREATE TABLE IF NOT EXISTS Aula (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  dataHora TEXT NOT NULL,
  capacidadeMaxima INTEGER NOT NULL,

  instrutor_id INTEGER NOT NULL,
  tipo_aula_id INTEGER NOT NULL,
  FOREIGN KEY (instrutor_id) REFERENCES Instrutor(id)
  FOREIGN KEY (tipo_aula_id) REFERENCES TipoDeAula(id)

);

CREATE TABLE IF NOT EXISTS Participa (
  praticante_id INTEGER NOT NULL,
  aula_id INTEGER NOT NULL,
  FOREIGN KEY(praticante_id) REFERENCES Praticante(id)
  FOREIGN KEY(aula_id) REFERENCES Praticante(id)

  PRIMARY KEY (praticante_id, aula_id)
)

