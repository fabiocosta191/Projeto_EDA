/**
 * @file funcao.h
 * @brief Definições de estruturas e protótipos de funções para manipulação de antenas e nefastos.
 * @author Fábio Rafael Gomes Costa
 * @contact a22997@alunos.ipca.pt
 * @course Engenharia Sistemas Informáticos
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHAS 100 /**< Número máximo de linhas na matriz. */
#define MAX_COLUNAS 100 /**< Número máximo de colunas na matriz. */

 /**
  * @brief Estrutura que representa uma antena.
  *
  * Esta estrutura armazena a frequência da antena e suas coordenadas (x, y).
  */
typedef struct ANT {
    char freqAntena; /**< Frequência da antena. */
    int x; /**< Coordenada x da antena. */
    int y; /**< Coordenada y da antena. */
    struct ANT* proxAntena; /**< Ponteiro para a próxima antena na lista. */
} ANT;

/**
 * @brief Estrutura que representa um nefasto.
 *
 * Esta estrutura armazena as coordenadas (x, y) de um nefasto.
 */
typedef struct NEF {
    int x; /**< Coordenada x do nefasto. */
    int y; /**< Coordenada y do nefasto. */
    struct NEF* proxNef; /**< Ponteiro para o próximo nefasto na lista. */
} NEF;

// Protótipos das funções

/**
 * @brief Insere uma nova antena na lista de antenas.
 *
 * @param lista Ponteiro para a lista de antenas.
 * @param freq Frequência da antena.
 * @param x Coordenada x da antena.
 * @param y Coordenada y da antena.
 */
void inserirAntena(ANT** lista, char freq, int x, int y);

/**
 * @brief Lê uma lista de antenas a partir de um arquivo e preenche uma matriz.
 *
 * @param nomeFicheiro Nome do arquivo a ser lido.
 * @param matriz Matriz onde os dados serão armazenados.
 * @param linhas Ponteiro para armazenar o número de linhas da matriz.
 * @param colunas Ponteiro para armazenar o número de colunas da matriz.
 * @return ANT* Retorna a lista de antenas lida do arquivo.
 */
ANT* LerLista(const char* nomeFicheiro, char matriz[MAX_LINHAS][MAX_COLUNAS], int* linhas, int* colunas);

/**
 * @brief Apresenta a lista de antenas.
 *
 * @param lista Lista de antenas a ser apresentada.
 */
void apresentarLista(ANT* lista);

/**
 * @brief Apresenta a matriz.
 *
 * @param matriz Matriz a ser apresentada.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 */
void apresentarMatriz(char matriz[MAX_LINHAS][MAX_COLUNAS], int linhas, int colunas);

/**
 * @brief Insere um nefasto na lista de nefastos.
 *
 * @param lista Ponteiro para a lista de nefastos.
 * @param x Coordenada x do nefasto.
 * @param y Coordenada y do nefasto.
 */
void inserirNefasto(NEF** lista, int x, int y);

/**
 * @brief Detecta e insere nefastos na matriz.
 *
 * @param matriz Matriz onde os nefastos serão inseridos.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 * @return NEF* Retorna a lista de nefastos detectados.
 */
NEF* matrizNefastos(char matriz[MAX_LINHAS][MAX_COLUNAS], int linhas, int colunas);

/**
 * @brief Apresenta a lista de nefastos.
 *
 * @param lista Lista de nefastos a ser apresentada.
 */
void apresentarListaNef(NEF* lista);

/**
 * @brief Copia os dados de uma matriz para outra.
 *
 * @param matrizNef Matriz de destino.
 * @param matriz Matriz de origem.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 */
void igualarMatrizes(char matrizNef[MAX_LINHAS][MAX_COLUNAS], char matriz[MAX_LINHAS][MAX_COLUNAS], int linhas, int colunas);

/**
 * @brief Atualiza a matriz e a lista de antenas com uma nova antena.
 *
 * @param lista Ponteiro para a lista de antenas.
 * @param freq Frequência da antena.
 * @param x Coordenada x da antena.
 * @param y Coordenada y da antena.
 * @param matriz Matriz a ser atualizada.
 */
void atualizarMatriz(ANT** lista, char freq, int x, int y, char matriz[MAX_LINHAS][MAX_COLUNAS]);

/**
 * @brief Remove uma antena da lista e da matriz.
 *
 * @param lista Ponteiro para a lista de antenas.
 * @param x Coordenada x da antena.
 * @param y Coordenada y da antena.
 * @param matriz Matriz a ser atualizada.
 */
void removerAntena(ANT** lista, int x, int y, char matriz[MAX_LINHAS][MAX_COLUNAS]);