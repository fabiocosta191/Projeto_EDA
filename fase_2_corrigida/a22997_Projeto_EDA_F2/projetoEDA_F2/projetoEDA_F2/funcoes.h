/**
 * @file funcao.h
 * @brief Definições de estruturas e protótipos de funções para manipulação de antenas e zonas nefastas.
 *
 * Este cabeçalho define as estruturas fundamentais usadas no projeto (antenas, arestas, grafo),
 * bem como as funções para leitura, travessia, análise, exportação e libertação de memória associadas à rede de antenas.
 * As estruturas são representadas em C com listas ligadas e listas de adjacência.
 *
 * A documentação segue o formato compatível com Doxygen.
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
    struct Ant* destinoAntena;   /**< Ponteiro para a antena de destino da ligação. */
    struct Ars* proximaAresta;   /**< Ponteiro para a próxima aresta na lista ligada. */
    int xNef;                    /**< Coordenada X da zona nefasta (se existir). */
    int yNef;                    /**< Coordenada Y da zona nefasta (se existir). */
} Ars;

/**
 * @struct Grafo
 * @brief Representa o grafo principal como uma lista ligada de vértices.
 */
typedef struct Grafo {
    struct Ant* Antena;          /**< Ponteiro para a antena armazenada neste nó do grafo. */
    struct Grafo* listaGrafo;    /**< Ponteiro para o próximo nó do grafo (lista ligada). */
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
 * @return Ponteiro para a estrutura do grafo, ou NULL em caso de erro.
 */
Grafo* LerLista(const char* nomeFicheiro, const char* tipoFicheiro, int* linhas, int* colunas);

/**
 * @brief Cria uma nova antena e insere na lista ligada.
 *
 * @param lista Lista atual de antenas.
 * @param freq Frequência da antena.
 * @param x Coordenada X da antena.
 * @param y Coordenada Y da antena.
 * @param id Identificador único da antena.
 * @return Ponteiro atualizado para a lista.
 */
Ant* CriarAntena(Ant* lista, char freq, int x, int y, int id);

/**
 * @brief Insere uma nova antena na estrutura do grafo.
 *
 * @param grafo Grafo atual.
 * @param lista Ponteiro para a nova antena a ser inserida.
 * @return Ponteiro atualizado para o grafo.
 */
Grafo* InserirAntena(Grafo* grafo, Ant* lista);

/**
 * @brief Cria as arestas entre antenas com base na frequência e calcula zonas nefastas.
 *
 * @param grafo Grafo com as antenas.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 * @return 200 em caso de sucesso, 501 em caso de erro.
 */
int CriarListaArestas(Grafo* grafo, int linhas, int colunas);

#pragma endregion

#pragma region DFS

/**
 * @brief Função recursiva que realiza a travessia em profundidade (DFS).
 *
 * @param atual Ponteiro para a antena atual.
 * @param visitado Vetor de controlo de visitados.
 * @param idOrigem ID da antena de origem.
 * @return 200.
 */
int DFS(Ant* atual, int visitado[], int idOrigem);

/**
 * @brief Inicia a travessia DFS a partir de uma antena de origem.
 *
 * @param grafo Ponteiro para o grafo.
 * @param idOrigem ID da antena inicial.
 * @return 200 se bem-sucedido, 500 se ID inválido.
 */
int IniciarDFS(Grafo* grafo, int idOrigem);

#pragma endregion

#pragma region BFS

/**
 * @brief Executa a travessia em largura (BFS) a partir de uma antena de origem.
 *
 * @param grafo Ponteiro para o grafo.
 * @param idOrigem ID da antena inicial.
 * @return 200 em caso de sucesso.
 */
int BFS(Grafo* grafo, int idOrigem);

#pragma endregion

#pragma region Todos_Caminhos

/**
 * @brief Função recursiva para encontrar todos os caminhos entre duas antenas.
 *
 * @param atual Antena atual no percurso.
 * @param idDestino ID da antena destino.
 * @param visitado Vetor de controlo de visitados.
 * @param caminho Vetor que armazena o caminho atual.
 * @param posicao Índice atual no vetor caminho.
 * @return 200.
 */
int EncontrarCaminhos(Ant* atual, int idDestino, int visitado[], int caminho[], int posicao);

/**
 * @brief Inicia a busca por todos os caminhos entre duas antenas.
 *
 * @param grafo Grafo com as antenas.
 * @param idOrigem ID da antena de origem.
 * @param idDestino ID da antena destino.
 * @return 200 em caso de sucesso, 500 se IDs forem inválidos.
 */
int TodosCaminhos(Grafo* grafo, int idOrigem, int idDestino);

#pragma endregion

#pragma region Exportar_Dados

/**
 * @brief Exporta a matriz de antenas para ficheiro .txt ou .bin.
 *
 * @param grafo Ponteiro para o grafo.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 * @param nomeFicheiro Nome base do ficheiro.
 * @param tipoFicheiro Extensão (".txt" ou ".bin").
 * @return 200 em sucesso, 500 em erro.
 */
int ExportarMatriz(Grafo* grafo, int linhas, int colunas, const char* nomeFicheiro, const char* tipoFicheiro);

#pragma endregion

#pragma region Impressao

/**
 * @brief Imprime a matriz com as antenas e zonas nefastas.
 *
 * @param grafo Ponteiro para o grafo.
 * @param linhas Número de linhas.
 * @param colunas Número de colunas.
 * @return 200.
 */
int ImprimirMatriz(Grafo* grafo, int linhas, int colunas);

/**
 * @brief Lista todas as antenas, arestas e zonas nefastas.
 *
 * @param grafo Ponteiro para o grafo.
 * @param linhas Número de linhas.
 * @param colunas Número de colunas.
 * @return 200.
 */
int ListarArestasENefastos(Grafo* grafo, int linhas, int colunas);

#pragma endregion

#pragma region Libertacao_Memoria

/**
 * @brief Liberta toda a memória alocada pelo grafo e antenas.
 *
 * @param grafo Ponteiro para o grafo.
 * @return 200 após libertação bem-sucedida.
 */
int FreeListaAntenas(Grafo* grafo);

#pragma endregion
