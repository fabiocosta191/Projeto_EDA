/**
 * @file funcao.h
 * @brief Definições de estruturas e protótipos de funções para manipulação de antenas e nefastos.
 * @author Fábio Rafael Gomes Costa
 * @contact a22997@alunos.ipca.pt
 * @course Engenharia Sistemas Informáticos
 * @version "Com correções pos defesa"
 * @date 04/04/2025
 */


#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /**
  * @def MAX_LINHAS
  * @brief Número máximo de linhas na matriz.
  */
#define MAX_LINHAS 100

  /**
   * @def MAX_COLUNAS
   * @brief Número máximo de colunas na matriz.
   */
#define MAX_COLUNAS 100

   /**
    * @struct Ant
    * @brief Estrutura que representa uma antena.
    *
    * Armazena informações sobre uma antena incluindo sua frequência,
    * coordenadas de posição e identificador único.
    */
typedef struct Ant {
    char freqAntena;    /**< Frequência da antena (carácter representativo). */
    int id;             /**< Identificador único da antena. */
    int x;              /**< Coordenada horizontal (coluna) da antena. */
    int y;              /**< Coordenada vertical (linha) da antena. */
    struct Ant* proxAntena; /**< Ponteiro para a próxima antena na lista ligada. */
} Ant;

/**
 * @struct Nef
 * @brief Estrutura que representa uma posição nefasta.
 *
 * Armazena coordenadas de posições onde podem ocorrer interferências
 * entre antenas, incluindo referências às antenas relacionadas.
 */
typedef struct Nef {
    int x;          /**< Coordenada horizontal da posição nefasta. */
    int y;          /**< Coordenada vertical da posição nefasta. */
    int antena1;    /**< ID da primeira antena associada ao nefasto. */
    int antena2;    /**< ID da segunda antena associada ao nefasto. */
    struct Nef* proxNef; /**< Ponteiro para o próximo nefasto na lista ligada. */
} Nef;

/**
 * @struct AntNef
 * @brief Estrutura que agrupa listas de antenas e posições nefastas.
 *
 * Permite manipular conjuntamente as listas de antenas e suas
 * posições nefastas relacionadas.
 */
typedef struct AntNef {
    struct Ant* lista;   /**< Ponteiro para a lista de antenas. */
    struct Nef* listaNef; /**< Ponteiro para a lista de posições nefastas. */
} AntNef;

/*----------------------------------------*/
/*         PROTÓTIPOS DE FUNÇÕES          */
/*----------------------------------------*/

/**
 * @defgroup Antenas Funções de Manipulação de Antenas
 * @brief Conjunto de funções para criação, leitura e manipulação de antenas.
 * @{
 */

 /**
  * @brief Cria e insere uma nova antena na lista.
  * @param lista Lista existente de antenas (pode ser NULL)
  * @param freq Carácter representando a frequência da antena
  * @param x Coordenada horizontal da antena
  * @param y Coordenada vertical da antena
  * @param id Identificador único para a nova antena
  * @return Ponteiro para a lista atualizada
  */
Ant* InserirAntena(Ant* lista, char freq, int x, int y, int id);

/**
 * @brief Lê um ficheiro e constrói a lista de antenas.
 * @param nomeFicheiro Nome base do ficheiro (sem extensão)
 * @param tipoFicheiro Extensão do ficheiro (".txt" ou outro)
 * @param linhas Ponteiro para armazenar número de linhas lidas
 * @param colunas Ponteiro para armazenar número máximo de colunas
 * @return Lista de antenas criada ou NULL em caso de erro
 */
Ant* LerLista(const char* nomeFicheiro, const char* tipoFicheiro, int* linhas, int* colunas);

/**
 * @brief Imprime no ecrã a lista de antenas.
 * @param lista Lista de antenas a ser exibida
 * @return 1 em caso de sucesso
 */
int ApresentarLista(Ant* lista);

/**
 * @brief Exibe uma representação matricial das antenas.
 * @param lista Lista de antenas
 * @param linhas Número de linhas da matriz
 * @param colunas Número de colunas da matriz
 * @return 1 em caso de sucesso
 */
int ApresentarMatrizLista(Ant* lista, int linhas, int colunas);

/**
 * @brief Remove uma antena da lista e atualiza posições nefastas.
 * @param listaAntNef Estrutura contendo ambas as listas
 * @param x Coordenada x da antena a remover
 * @param y Coordenada y da antena a remover
 * @return Estrutura atualizada
 */
AntNef* RemoverAntena(AntNef* listaAntNef, int x, int y);

/**
 * @brief Adiciona ou atualiza uma antena na lista.
 * @param listaAntNef Estrutura contendo ambas as listas
 * @param freq Frequência da nova antena
 * @param x Coordenada x da antena
 * @param y Coordenada y da antena
 * @param linhas Total de linhas da área
 * @param colunas Total de colunas da área
 * @return Estrutura atualizada
 */
AntNef* AdicionarAntena(AntNef* listaAntNef, char freq, int x, int y, int linhas, int colunas);

/** @} */ // Fim do grupo Antenas

/**
 * @defgroup Nefastos Funções de Manipulação de Nefastos
 * @brief Conjunto de funções para cálculo e manipulação de posições nefastas.
 * @{
 */

 /**
  * @brief Insere uma nova posição nefasta na lista.
  * @param listaNef Lista existente de nefastos
  * @param x Coordenada x da posição nefasta
  * @param y Coordenada y da posição nefasta
  * @param ant1 ID da primeira antena relacionada
  * @param ant2 ID da segunda antena relacionada
  * @param lista Lista de antenas para validação
  * @return Lista atualizada de nefastos
  */
Nef* InserirNefasto(Nef* listaNef, int x, int y, int ant1, int ant2, Ant* lista);

/**
 * @brief Calcula posições nefastas entre antenas.
 * @param lista Lista de antenas a analisar
 * @param linhas Número de linhas da área
 * @param colunas Número de colunas da área
 * @return Lista de posições nefastas encontradas
 */
Nef* EncontrarNefastos(Ant* lista, int linhas, int colunas);

/**
 * @brief Imprime no ecrã a lista de posições nefastas.
 * @param listaNef Lista de nefastos a exibir
 * @return 1 em caso de sucesso
 */
int ApresentarListaNef(Nef* listaNef);

/**
 * @brief Exibe matriz com antenas e posições nefastas.
 * @param lista Lista de antenas
 * @param linhas Número de linhas da matriz
 * @param colunas Número de colunas da matriz
 * @param listaNef Lista de posições nefastas
 * @return 1 em caso de sucesso
 */
int ApresentarMatrizListaNef(Ant* lista, int linhas, int colunas, Nef* listaNef);

/** @} */ // Fim do grupo Nefastos

/**
 * @defgroup Memoria Funções de Gestão de Memória
 * @brief Funções para libertação de memória alocada.
 * @{
 */

 /**
  * @brief Liberta memória alocada para lista de antenas.
  * @param lista Lista a ser liberada
  * @return 1 em caso de sucesso
  */
int FreeLista(Ant* lista);

/**
 * @brief Liberta memória alocada para lista de nefastos.
 * @param listaNef Lista a ser liberada
 * @return 1 em caso de sucesso
 */
int FreeListaNef(Nef* listaNef);
/**
 * @brief Liberta memória alocada para ambas as listas.
 * @param lista Lista de antenas a ser liberada
 * @param listaNef Lista de nefastos a ser liberada
 * @return 1 em caso de sucesso
 */
int FreeAntNef(AntNef* listaAntNef);
    /** @} */ // Fim do grupo Memoria