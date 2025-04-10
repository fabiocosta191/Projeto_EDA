/**
 * @file funcao.h
 * @brief Defini��es de estruturas e prot�tipos de fun��es para manipula��o de antenas e nefastos.
 * @author F�bio Rafael Gomes Costa
 * @contact a22997@alunos.ipca.pt
 * @course Engenharia Sistemas Inform�ticos
 * @version "Com corre��es pos defesa"
 * @date 04/04/2025
 */


#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /**
  * @def MAX_LINHAS
  * @brief N�mero m�ximo de linhas na matriz.
  */
#define MAX_LINHAS 100

  /**
   * @def MAX_COLUNAS
   * @brief N�mero m�ximo de colunas na matriz.
   */
#define MAX_COLUNAS 100

   /**
    * @struct Ant
    * @brief Estrutura que representa uma antena.
    *
    * Armazena informa��es sobre uma antena incluindo sua frequ�ncia,
    * coordenadas de posi��o e identificador �nico.
    */
typedef struct Ant {
    char freqAntena;    /**< Frequ�ncia da antena (car�cter representativo). */
    int id;             /**< Identificador �nico da antena. */
    int x;              /**< Coordenada horizontal (coluna) da antena. */
    int y;              /**< Coordenada vertical (linha) da antena. */
    struct Ant* proxAntena; /**< Ponteiro para a pr�xima antena na lista ligada. */
} Ant;

/**
 * @struct Nef
 * @brief Estrutura que representa uma posi��o nefasta.
 *
 * Armazena coordenadas de posi��es onde podem ocorrer interfer�ncias
 * entre antenas, incluindo refer�ncias �s antenas relacionadas.
 */
typedef struct Nef {
    int x;          /**< Coordenada horizontal da posi��o nefasta. */
    int y;          /**< Coordenada vertical da posi��o nefasta. */
    int antena1;    /**< ID da primeira antena associada ao nefasto. */
    int antena2;    /**< ID da segunda antena associada ao nefasto. */
    struct Nef* proxNef; /**< Ponteiro para o pr�ximo nefasto na lista ligada. */
} Nef;

/**
 * @struct AntNef
 * @brief Estrutura que agrupa listas de antenas e posi��es nefastas.
 *
 * Permite manipular conjuntamente as listas de antenas e suas
 * posi��es nefastas relacionadas.
 */
typedef struct AntNef {
    struct Ant* lista;   /**< Ponteiro para a lista de antenas. */
    struct Nef* listaNef; /**< Ponteiro para a lista de posi��es nefastas. */
} AntNef;

/*----------------------------------------*/
/*         PROT�TIPOS DE FUN��ES          */
/*----------------------------------------*/

/**
 * @defgroup Antenas Fun��es de Manipula��o de Antenas
 * @brief Conjunto de fun��es para cria��o, leitura e manipula��o de antenas.
 * @{
 */

 /**
  * @brief Cria e insere uma nova antena na lista.
  * @param lista Lista existente de antenas (pode ser NULL)
  * @param freq Car�cter representando a frequ�ncia da antena
  * @param x Coordenada horizontal da antena
  * @param y Coordenada vertical da antena
  * @param id Identificador �nico para a nova antena
  * @return Ponteiro para a lista atualizada
  */
Ant* InserirAntena(Ant* lista, char freq, int x, int y, int id);

/**
 * @brief L� um ficheiro e constr�i a lista de antenas.
 * @param nomeFicheiro Nome base do ficheiro (sem extens�o)
 * @param tipoFicheiro Extens�o do ficheiro (".txt" ou outro)
 * @param linhas Ponteiro para armazenar n�mero de linhas lidas
 * @param colunas Ponteiro para armazenar n�mero m�ximo de colunas
 * @return Lista de antenas criada ou NULL em caso de erro
 */
Ant* LerLista(const char* nomeFicheiro, const char* tipoFicheiro, int* linhas, int* colunas);

/**
 * @brief Imprime no ecr� a lista de antenas.
 * @param lista Lista de antenas a ser exibida
 * @return 1 em caso de sucesso
 */
int ApresentarLista(Ant* lista);

/**
 * @brief Exibe uma representa��o matricial das antenas.
 * @param lista Lista de antenas
 * @param linhas N�mero de linhas da matriz
 * @param colunas N�mero de colunas da matriz
 * @return 1 em caso de sucesso
 */
int ApresentarMatrizLista(Ant* lista, int linhas, int colunas);

/**
 * @brief Remove uma antena da lista e atualiza posi��es nefastas.
 * @param listaAntNef Estrutura contendo ambas as listas
 * @param x Coordenada x da antena a remover
 * @param y Coordenada y da antena a remover
 * @return Estrutura atualizada
 */
AntNef* RemoverAntena(AntNef* listaAntNef, int x, int y);

/**
 * @brief Adiciona ou atualiza uma antena na lista.
 * @param listaAntNef Estrutura contendo ambas as listas
 * @param freq Frequ�ncia da nova antena
 * @param x Coordenada x da antena
 * @param y Coordenada y da antena
 * @param linhas Total de linhas da �rea
 * @param colunas Total de colunas da �rea
 * @return Estrutura atualizada
 */
AntNef* AdicionarAntena(AntNef* listaAntNef, char freq, int x, int y, int linhas, int colunas);

/** @} */ // Fim do grupo Antenas

/**
 * @defgroup Nefastos Fun��es de Manipula��o de Nefastos
 * @brief Conjunto de fun��es para c�lculo e manipula��o de posi��es nefastas.
 * @{
 */

 /**
  * @brief Insere uma nova posi��o nefasta na lista.
  * @param listaNef Lista existente de nefastos
  * @param x Coordenada x da posi��o nefasta
  * @param y Coordenada y da posi��o nefasta
  * @param ant1 ID da primeira antena relacionada
  * @param ant2 ID da segunda antena relacionada
  * @param lista Lista de antenas para valida��o
  * @return Lista atualizada de nefastos
  */
Nef* InserirNefasto(Nef* listaNef, int x, int y, int ant1, int ant2, Ant* lista);

/**
 * @brief Calcula posi��es nefastas entre antenas.
 * @param lista Lista de antenas a analisar
 * @param linhas N�mero de linhas da �rea
 * @param colunas N�mero de colunas da �rea
 * @return Lista de posi��es nefastas encontradas
 */
Nef* EncontrarNefastos(Ant* lista, int linhas, int colunas);

/**
 * @brief Imprime no ecr� a lista de posi��es nefastas.
 * @param listaNef Lista de nefastos a exibir
 * @return 1 em caso de sucesso
 */
int ApresentarListaNef(Nef* listaNef);

/**
 * @brief Exibe matriz com antenas e posi��es nefastas.
 * @param lista Lista de antenas
 * @param linhas N�mero de linhas da matriz
 * @param colunas N�mero de colunas da matriz
 * @param listaNef Lista de posi��es nefastas
 * @return 1 em caso de sucesso
 */
int ApresentarMatrizListaNef(Ant* lista, int linhas, int colunas, Nef* listaNef);

/** @} */ // Fim do grupo Nefastos

/**
 * @defgroup Memoria Fun��es de Gest�o de Mem�ria
 * @brief Fun��es para liberta��o de mem�ria alocada.
 * @{
 */

 /**
  * @brief Liberta mem�ria alocada para lista de antenas.
  * @param lista Lista a ser liberada
  * @return 1 em caso de sucesso
  */
int FreeLista(Ant* lista);

/**
 * @brief Liberta mem�ria alocada para lista de nefastos.
 * @param listaNef Lista a ser liberada
 * @return 1 em caso de sucesso
 */
int FreeListaNef(Nef* listaNef);
/**
 * @brief Liberta mem�ria alocada para ambas as listas.
 * @param lista Lista de antenas a ser liberada
 * @param listaNef Lista de nefastos a ser liberada
 * @return 1 em caso de sucesso
 */
int FreeAntNef(AntNef* listaAntNef);
    /** @} */ // Fim do grupo Memoria