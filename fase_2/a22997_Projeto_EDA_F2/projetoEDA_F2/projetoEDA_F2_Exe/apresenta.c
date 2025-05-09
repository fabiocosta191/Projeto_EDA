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
    printf("\n\n");
	return 200;
}


int ListarArestasENefastos(Grafo* grafo, int linhas, int colunas) {
    
    printf("\nLista de Antenas, Arestas e Zonas Nefastas:\n");

    for (int i = 0; i < MAX_VERTICES; i++) {
        Ant* ant = grafo->Antena[i];
        if (ant == NULL)
            continue;

        printf("\nAntena %d (freq. %c) em [%d, %d]:\n", ant->id, ant->freqAntena, ant->x, ant->y);

        Ars* aresta = ant->listaAresta;
        int count = 0;
        if (aresta == NULL) {
            printf("  - Sem arestas.\n");
        }

        while (aresta != NULL) {
            int xNef = aresta->xNef;
            int yNef = aresta->yNef;
            int nefastoValido = (xNef >= 0 && xNef < colunas && yNef >= 0 && yNef < linhas);

            printf("  Aresta %d -> Antena %d (%c) em [%d, %d] | ",
                count,
                aresta->destinoAntena->id,
                aresta->destinoAntena->freqAntena,
                aresta->destinoAntena->x,
                aresta->destinoAntena->y);

            if (nefastoValido) {
                printf("Zona nefasta: [%d, %d]\n", xNef, yNef);
            }
            else {
                printf("Nao possui zona nefasta guardada, ou esta encontra-se fora dos limites da matriz.\n");
            }

            count++;
            aresta = aresta->proximaAresta;
        }
    }
	printf("\n\n");
	return 200;
}
