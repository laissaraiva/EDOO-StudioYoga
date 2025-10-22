cmake_minimum_required(VERSION 3.10)

project(Projet CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PUBLIC include)

set(SOURCES
    src/*
)

add_executable(${PROJECT_NAME} ${SOURCES})
