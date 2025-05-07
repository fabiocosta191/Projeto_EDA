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



typedef struct Ant { //Antena == Vertice
    char freqAntena;    /**< Frequ?ncia da antena (car?cter representativo). */
    int id;             /**< Identificador ?nico da antena. */
    int x;              /**< Coordenada horizontal (coluna) da antena. */
    int y;              /**< Coordenada vertical (linha) da antena. */
    struct Ant* proxAntena; /**< Ponteiro para a pr?xima antena na lista ligada. */
    struct Ars* listaAresta;
} Ant;

typedef struct Ars {
    struct Ant* destinoAntena;
    struct Ars* proximaAresta;
}Ars;

typedef struct Grafo {
    //array que armazena endere�os de Ant
    struct Ant* Antena[MAX_VERTICES]; //Antena[0]= Endere�o de Antena 0
}Grafo;



Ant* LerLista(const char* nomeFicheiro, const char* tipoFicheiro, int* linhas, int* colunas, Grafo* grafo);
Ant* InserirAntena(Ant* lista, Grafo* grafo, char freq, int x, int y, int id);
int CriarListaArestas(Ant* lista);

