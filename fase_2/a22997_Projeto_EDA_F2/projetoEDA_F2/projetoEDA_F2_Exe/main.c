/**
 * @file main.c
 * @brief Ponto de entrada principal do programa que manipula grafos de antenas.
 *
 * Este ficheiro contém o `main`, responsável por:
 * - Carregar as antenas a partir de um ficheiro;
 * - Imprimir a matriz de antenas e zonas nefastas;
 * - Listar todas as arestas e as zonas nefastas associadas;
 * - Realizar travessias DFS e BFS a partir de uma antena escolhida;
 * - Encontrar todos os caminhos entre duas antenas;
 * - Libertar a memória alocada dinamicamente no final.
 *
 * @author Fábio Rafael Gomes Costa
 * @date 18/05/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

 /**
  * @brief Função principal do programa.
  *
  * Executa uma sequência de operações sobre um grafo de antenas, carregado a partir de um ficheiro.
  * As operações incluem impressão da matriz, listagem de arestas, execução de DFS, BFS e descoberta
  * de todos os caminhos entre dois nós. Ao final, toda a memória alocada é libertada.
  *
  * @return int Retorna 0 se a execução for bem-sucedida, ou 1 em caso de erro.
  */
int main() {
    Grafo grafo;
    Ant* listaAntenas = NULL;
    int linhas = 0, colunas = 0;
    int validacaoResultado = 0;

    // Leitura da matriz do ficheiro "antenas.txt"
    listaAntenas = LerLista("antenas", ".txt", &linhas, &colunas, &grafo);
    if (listaAntenas == NULL) {
        perror("Erro ao carregar a lista de antenas.\n");
        return 1;
    }

    // Imprime a matriz com antenas e zonas nefastas
    validacaoResultado = ImprimirMatriz(&grafo, linhas, colunas);
    if (validacaoResultado != 200) {
        perror("Erro ao imprimir a matriz.\n");
    }

    // Lista as arestas e zonas nefastas
    validacaoResultado = ListarArestasENefastos(&grafo, linhas, colunas);
    if (validacaoResultado != 200) {
        perror("Erro ao imprimir lista.\n");
    }

    // Executa a procura em profundidade (DFS) a partir da antena 3
    validacaoResultado = IniciarDFS(&grafo, 3);
    if (validacaoResultado != 200) {
        perror("Erro na procura em profundidade.\n");
    }

    // Executa a procura em largura (BFS) a partir da antena 3
    validacaoResultado = BFS(&grafo, 3);
    if (validacaoResultado != 200) {
        perror("Erro na procura em largura.\n");
    }

    // Encontra todos os caminhos possíveis entre a antena 1 e 6
    validacaoResultado = TodosCaminhos(&grafo, 1, 6);
    if (validacaoResultado != 200) {
        perror("Erro na procura ao encontrar o caminho.\n");
    }

    // Liberta toda a memória alocada
    validacaoResultado = FreeListaAntenas(listaAntenas, &grafo);
    if (validacaoResultado != 200) {
        perror("Erro ao libertar memoria.\n");
    }
    else {
        printf("Memoria libertada com sucesso.\n");
    }

    return 0;
}
