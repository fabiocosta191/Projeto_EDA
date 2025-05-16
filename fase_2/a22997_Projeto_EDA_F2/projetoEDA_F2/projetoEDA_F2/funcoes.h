/**
 * @file funcao.h
 * @brief Definições de estruturas e protótipos de funções para manipulação de antenas e zonas nefastas.
 *
 * Este cabeçalho define as estruturas fundamentais usadas no projeto (antenas, arestas, grafo)
 * bem como as funções para leitura, travessia, análise e libertação de memória associadas à rede de antenas.
 *
 * @author Fábio Rafael Gomes Costa
 * @contact a22997@alunos.ipca.pt
 * @course Engenharia de Sistemas Informáticos
 * @date 18/05/2025
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHAS 100           /**< Número máximo de linhas da matriz. */
#define MAX_COLUNAS 100          /**< Número máximo de colunas da matriz. */
#define MAX_VERTICES 200         /**< Número máximo de antenas (vértices) no grafo. */

#pragma region Estrutura_grafo

 /**
  * @struct Ant
  * @brief Representa uma antena (ou vértice) do grafo.
  */
typedef struct Ant {
    char freqAntena;             /**< Frequência da antena (ex: '0', 'A', etc). */
    int id;                      /**< Identificador único da antena. */
    int x;                       /**< Coordenada horizontal (coluna) da antena. */
    int y;                       /**< Coordenada vertical (linha) da antena. */
    struct Ant* proxAntena;      /**< Ponteiro para a próxima antena na lista ligada. */
    struct Ars* listaAresta;     /**< Ponteiro para a lista de arestas associadas a esta antena. */
} Ant;

/**
 * @struct Ars
 * @brief Representa uma aresta entre duas antenas, podendo conter a zona nefasta.
 */
typedef struct Ars {
    struct Ant* origemAntena;    /**< Ponteiro para a antena de origem da ligação. */
    struct Ant* destinoAntena;   /**< Ponteiro para a antena de destino da ligação. */
    struct Ars* proximaAresta;   /**< Ponteiro para a próxima aresta na lista ligada. */
    int xNef;                    /**< Coordenada X da zona nefasta (se existir). */
    int yNef;                    /**< Coordenada Y da zona nefasta (se existir). */
} Ars;

/**
 * @struct Grafo
 * @brief Representa o grafo principal através de um array de ponteiros para antenas.
 */
typedef struct Grafo {
    struct Ant* Antena[MAX_VERTICES]; /**< Array que armazena os ponteiros para antenas indexadas pelo seu ID. */
} Grafo;

#pragma endregion

#pragma region Leitura_Armazenamento

/**
 * @brief Lê um ficheiro com a matriz de antenas e cria a lista ligada e o grafo correspondente.
 *
 * @param nomeFicheiro Nome base do ficheiro (sem extensão).
 * @param tipoFicheiro Extensão do ficheiro (".txt" ou ".bin").
 * @param linhas Ponteiro onde será armazenado o número de linhas lidas.
 * @param colunas Ponteiro onde será armazenado o número de colunas lidas.
 * @param grafo Ponteiro para a estrutura do grafo a ser preenchida.
 * @return Ponteiro para o início da lista ligada de antenas.
 */
Ant* LerLista(const char* nomeFicheiro, const char* tipoFicheiro, int* linhas, int* colunas, Grafo* grafo);

/**
 * @brief Insere uma nova antena na lista e no grafo.
 *
 * @param lista Lista atual de antenas.
 * @param grafo Ponteiro para o grafo.
 * @param freq Carácter da frequência da antena.
 * @param x Coordenada X da antena.
 * @param y Coordenada Y da antena.
 * @param id Identificador único da antena.
 * @return Ponteiro para a nova cabeça da lista ligada.
 */
Ant* InserirAntena(Ant* lista, Grafo* grafo, char freq, int x, int y, int id);

/**
 * @brief Cria as arestas entre antenas com base na frequência e calcula zonas nefastas.
 *
 * @param lista Lista de antenas.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 * @return 200 em caso de sucesso, ou 500 em caso de erro de alocação.
 */
int CriarListaArestas(Ant* lista, int linhas, int colunas);

#pragma endregion

#pragma region DFS

/**
 * @brief Função recursiva que realiza a travessia em profundidade (DFS).
 *
 * @param atual Ponteiro para a antena atual.
 * @param visitado Vetor de controlo de visitados.
 * @param idOrigem ID da antena anterior (para rastreamento).
 * @return 200 em caso de sucesso.
 */
int DFS(Ant* atual, int visitado[], int idOrigem);

/**
 * @brief Inicia a travessia DFS a partir de uma antena de origem.
 *
 * @param grafo Ponteiro para o grafo.
 * @param idOrigem ID da antena de origem.
 * @return 200 se bem-sucedido, 500 se o ID for inválido.
 */
int IniciarDFS(Grafo* grafo, int idOrigem);

#pragma endregion

#pragma region BFS

/**
 * @brief Executa a travessia em largura (BFS) a partir de uma antena de origem.
 *
 * @param grafo Ponteiro para o grafo.
 * @param idOrigem ID da antena de origem.
 * @return 200 em caso de sucesso.
 */
int BFS(Grafo* grafo, int idOrigem);

#pragma endregion

#pragma region Todos_Caminhos

/**
 * @brief Função recursiva para descobrir todos os caminhos entre duas antenas.
 *
 * @param atual Antena atual no percurso.
 * @param idDestino ID da antena destino.
 * @param visitado Vetor de controlo de visitados.
 * @param caminho Vetor para armazenar o caminho atual.
 * @param posicao Posição atual no vetor de caminho.
 * @return 200 em caso de sucesso.
 */
int EncontrarCaminhos(Ant* atual, int idDestino, int visitado[], int caminho[], int posicao);

/**
 * @brief Inicia a busca por todos os caminhos possíveis entre duas antenas.
 *
 * @param grafo Grafo com todas as antenas.
 * @param idOrigem ID da antena de origem.
 * @param idDestino ID da antena de destino.
 * @return 200 em caso de sucesso.
 */
int TodosCaminhos(Grafo* grafo, int idOrigem, int idDestino);

#pragma endregion

#pragma region Impressao

/**
 * @brief Imprime a matriz com a posição das antenas.
 *
 * @param grafo Ponteiro para o grafo.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 * @return 200 em caso de sucesso.
 */
int ImprimirMatriz(Grafo* grafo, int linhas, int colunas);

/**
 * @brief Lista todas as arestas existentes e suas zonas nefastas (se existirem).
 *
 * @param grafo Ponteiro para o grafo.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 * @return 200 em caso de sucesso.
 */
int ListarArestasENefastos(Grafo* grafo, int linhas, int colunas);

#pragma endregion

#pragma region Libertacao_Memoria

/**
 * @brief Liberta a memória alocada para a lista de antenas e suas arestas.
 *
 * @param lista Lista de antenas.
 * @param grafo Grafo a ser limpo.
 * @return 200 após a libertação completa.
 */
int FreeListaAntenas(Ant* lista, Grafo* grafo);

#pragma endregion
