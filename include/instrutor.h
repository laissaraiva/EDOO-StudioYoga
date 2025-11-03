#ifndef INSTRUTOR_H
#define INSTRUTOR_H

#include "Pessoa.h"  
#include <string>
#include <vector>

class Aula;  //declaração da class Aula

class Instrutor : public Pessoa {
public:
    /**
     * @brief Construtor da classe Instrutor.
     * @param nome O nome do instrutor (passado para Pessoa).
     * @param cpf O CPF do instrutor (passado para Pessoa).
     * @param genero O gênero do instrutor (passado para Pessoa).
     * @param especialidade A especialidade de yoga do instrutor.
     */
    Instrutor(const std::string& nome, 
              const std::string& cpf, 
              const std::string& genero, 
              const std::string& especialidade);

    /**
     * @brief Destrutor virtual.
     */
    virtual ~Instrutor();


    /**
     * @brief Exibe os detalhes completos do instrutor.
     * Esta função sobrescreve (override) a função virtual pura de Pessoa.
     */
    virtual void exibirDetalhes() const override;


    void setEspecialidade(const std::string& novaEspecialidade);
    std::string getEspecialidade() const;


    /**
     * @brief Adiciona uma aula à lista de aulas ministradas.
     * @param aula Um ponteiro para o objeto Aula a ser adicionado.
     */
    void adicionarAula(Aula* aula);

    /**
     * @brief Lista (imprime no console) todas as aulas ministradas.
     */
    void listarAulasMinistradas() const;

private:
    std::string m_especialidade;
    
    std::vector<Aula*> m_aulasMinistradas; 
};

#endif //INSTRUTOR_H