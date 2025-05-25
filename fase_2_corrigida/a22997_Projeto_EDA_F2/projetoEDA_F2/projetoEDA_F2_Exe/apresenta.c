/**
 * @file apresenta.c
 * @brief Implementação de funções para apresentação de dados do grafo (matriz e lista de arestas).
 *
 * Contém funções responsáveis por mostrar graficamente a matriz de antenas e os efeitos nefastos,
 * bem como listar todas as antenas, suas ligações (arestas) e zonas nefastas associadas.
 *
 * @author Fábio Rafael Gomes Costa
 * @contact a22997@alunos.ipca.pt
 * @course Engenharia Sistemas Informáticos
 * @date 04/04/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"




int ImprimirMatriz(Grafo* grafo, int linhas, int colunas) {
    for (int y = 0; y < linhas; y++) {
        for (int x = 0; x < colunas; x++) {
            int marcado = 0;

            // Percorrer lista ligada de antenas
            Ant* atual = grafo->Antena;
            while (atual != NULL) {
                if (atual->x == x && atual->y == y) {
                    printf("%c ", atual->freqAntena);
                    marcado = 1;
                    break;
                }
                atual = atual->proxAntena;
            }

            if (marcado) continue;

            // Percorrer zonas nefastas
            atual = grafo->Antena;
            while (atual != NULL) {
                Ars* aresta = atual->listaAresta;
                while (aresta != NULL) {
                    if (aresta->xNef == x && aresta->yNef == y) {
                        printf("# ");
                        marcado = 1;
                        break;
                    }
                    aresta = aresta->proximaAresta;
                }
                if (marcado) break;
                atual = atual->proxAntena;
            }

            if (!marcado) printf(". ");
        }
        printf("\n");
    }
    printf("\n\n");
    return 200;
}




int ListarArestasENefastos(Grafo* grafo, int linhas, int colunas) {
    printf("\nLista de Antenas, Arestas e Zonas Nefastas:\n");

    Ant* ant = grafo->Antena;  // Ponto de partida da lista ligada
    while (ant != NULL) {
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

        ant = ant->proxAntena;  // Avança para a próxima antena na lista
    }

    printf("\n\n");
    return 200;
}
