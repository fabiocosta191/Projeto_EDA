/**
 * @file apresenta.c
 * @brief Implementa��o de funcoes para apresentar Dados.
 * @author Fabio Rafael Gomes Costa
 * @contact a22997@alunos.ipca.pt
 * @course Engenharia Sistemas Informaticos
 * @date 04/04/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int ImprimirMatriz(Grafo* grafo, int linhas, int colunas) {
    //printf("Matriz com Antenas e Efeitos Nefastos:\n");

    for (int y = 0; y < linhas; y++) {
        for (int x = 0; x < colunas; x++) {
            int marcado = 0;

            // Verifica se existe uma antena nesta posição
            for (int i = 0; i < MAX_VERTICES && grafo->Antena[i] != NULL; i++) {
                if (grafo->Antena[i]->x == x && grafo->Antena[i]->y == y) {
                    printf("%c ", grafo->Antena[i]->freqAntena);
                    marcado = 1;
                    break;
                }
            }

			if (marcado) continue; // Se já foi marcado, não precisa verificar os nefastos

            // Verifica se existe um ponto nefasto nesta posição
            for (int i = 0; i < MAX_VERTICES && grafo->Antena[i] != NULL; i++) {
                Ars* aresta = grafo->Antena[i]->listaAresta;
                while (aresta != NULL) {
                    if (aresta->xNef == x && aresta->yNef == y) {
                        printf("# ");
                        marcado = 1;
                        break;
                    }
                    aresta = aresta->proximaAresta;
                }
                if (marcado) break;
            }

            if (!marcado) {
                printf(". ");
            }
        }
        printf("\n");
    }
	return 200;
}