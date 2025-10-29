cmake_minimum_required(VERSION 3.28)

project(Studio-Yoga)

add_executable(Studio-Yoga
   #Arquivo fonte do sqlite3 no modo almagamation
   src/sqlite3.c

   src/main.cpp
   src/Aula.cpp
   src/HotYoga.cpp
   src/Instrutor.cpp
   src/Pessoa.cpp
   src/Plano.cpp
   src/Praticante.cpp
   src/TipoDeAula.cpp
   src/YogaComPets.cpp
   src/YogaTradicional.cpp
   src/databaseManager.cpp
)

target_include_directories(Studio-Yoga PUBLIC include)

if(UNIX)
  target_link_libraries(Studio-Yoga PUBLIC pthread dl)
endif()
