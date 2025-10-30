cmake_minimum_required(VERSION 3.28)

project(Studio-Yoga)

add_executable(Studio-Yoga
   #Arquivo fonte do sqlite3 no modo almagamation
   src/sqlite3.c
   src/main.cpp

   src/services/Aula.cpp
   src/services/HotYoga.cpp
   src/services/Instrutor.cpp
   src/services/Pessoa.cpp
   src/services/Plano.cpp
   src/services/Praticante.cpp
   src/services/TipoDeAula.cpp
   src/services/YogaComPets.cpp
   src/services/YogaTradicional.cpp

   src/repository/AulaRepository.cpp
   src/repository/HotYogaRepository.cpp
   src/repository/InstrutorRepository.cpp
   src/repository/PessoaRepository.cpp
   src/repository/PlanoRepository.cpp
   src/repository/PraticanteRepository.cpp
   src/repository/TipoDeAulaRepository.cpp
   src/repository/YogaComPetsRepository.cpp
   src/repository/YogaTradicionalRepository.cpp
   src/repository/databaseManager.cpp
)

target_include_directories(Studio-Yoga PUBLIC
   include
   include/services
   include/repository
)

if(UNIX)
  target_link_libraries(Studio-Yoga PUBLIC pthread dl)
endif()
