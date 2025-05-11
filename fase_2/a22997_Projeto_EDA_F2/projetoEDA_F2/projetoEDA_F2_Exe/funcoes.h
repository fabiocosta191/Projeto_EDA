/**
 * @file funcao.h
 * @brief Defini??es de estruturas e prot?tipos de fun??es para manipula??o de antenas e nefastos.
 * @author F?bio Rafael Gomes Costa
 * @contact a22997@alunos.ipca.pt
 * @course Engenharia Sistemas Inform?ticos
 * @date 07/05/2025
 */


#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX_LINHAS 100
#define MAX_COLUNAS 100
#define MAX_VERTICES 200


#pragma region Estrutura_grafo
typedef struct Ant { //Antena == Vertice
    char freqAntena;    /**< Frequ?ncia da antena (car?cter representativo). */
    int id;             /**< Identificador ?nico da antena. */
    int x;              /**< Coordenada horizontal (coluna) da antena. */
    int y;              /**< Coordenada vertical (linha) da antena. */
    struct Ant* proxAntena; /**< Ponteiro para a pr?xima antena na lista ligada. */
	struct Ars* listaAresta; // Lista de arestas
} Ant;

typedef struct Ars {
    struct Ant* origemAntena; //Antena Origem
    struct Ant* destinoAntena;//Antena Destino
	struct Ars* proximaAresta;//Proxima Aresta
	int xNef;// Coordenada X do nefasto
	int yNef;// Coordenada Y do nefasto
}Ars;

typedef struct Grafo {
    struct Ant* Antena[MAX_VERTICES]; //Antena[id]= Endereço de Antena id
}Grafo;
#pragma endregion


#pragma region Leitura_Armazenamento
Ant* LerLista(const char* nomeFicheiro, const char* tipoFicheiro, int* linhas, int* colunas, Grafo* grafo);
Ant* InserirAntena(Ant* lista, Grafo* grafo, char freq, int x, int y, int id);
int CriarListaArestas(Ant* lista, int linhas, int colunas);
#pragma endregion


#pragma region DFS
int DFS(Ant* atual, int visitado[], int idOrigem);
int IniciarDFS(Grafo* grafo, int idOrigem);
#pragma endregion


#pragma region BFS
int BFS(Grafo* grafo, int idOrigem);
#pragma endregion


#pragma region Todos_Caminhos
int EncontrarCaminhos(Ant* atual, int idDestino, int visitado[], int caminho[], int posicao);
int TodosCaminhos(Grafo* grafo, int idOrigem, int idDestino);
#pragma endregion


#pragma region Impressao
int ImprimirMatriz(Grafo* grafo, int linhas, int colunas);
int ListarArestasENefastos(Grafo* grafo, int linhas, int colunas);
#pragma endregion


#pragma region Libertacao_Memoria
//* Funcao para liberar a memoria alocada para a lista de antenas, grafo, vertice */
int FreeListaAntenas(Ant* lista, Grafo* grafo);
#pragma endregion
