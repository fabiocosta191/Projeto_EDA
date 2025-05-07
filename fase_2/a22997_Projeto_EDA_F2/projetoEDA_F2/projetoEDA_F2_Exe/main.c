#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"


int main() {
    Grafo grafo;
    Ant* listaAntenas = NULL;
    int linhas = 0, colunas = 0;

    // Substitui "matriz" e ".txt" pelos nomes reais do teu ficheiro
    listaAntenas = LerLista("antenas", ".txt", &linhas, &colunas, &grafo);

    if (listaAntenas == NULL) {
        printf("Erro ao carregar a lista de antenas.\n");
        return 1;
    }

    printf("Matriz de Antenas:\n");
    for (int y = 0; y < linhas; y++) {
        for (int x = 0; x < colunas; x++) {
            int encontrado = 0;
            for (Ant* ant = listaAntenas; ant != NULL; ant = ant->proxAntena) {
                if (ant->x == x && ant->y == y) {
                    printf("%c ", ant->freqAntena);
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                printf(". ");
            }
        }
        printf("\n");
    }

   
    printf("\nLista de Antenas e suas Arestas:\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        Ant* ant = grafo.Antena[i];
        if (ant != NULL) {
            printf("Antena %d (%c) [x=%d, y=%d]\n", ant->id, ant->freqAntena, ant->x, ant->y);
            Ars* aresta = ant->listaAresta;
            int count = 0;
            while (aresta != NULL) {
                printf("  Aresta %d -> Antena %d (%c) [x=%d, y=%d]\n",
                    count, aresta->destinoAntena->id,
                    aresta->destinoAntena->freqAntena,
                    aresta->destinoAntena->x, aresta->destinoAntena->y);
                count++;
                aresta = aresta->proximaAresta;
            }
        }
    }
	// Liberta a memória alocada
    FreeListaAntenas(listaAntenas);
    FreeGrafo(&grafo);

    return 0;
}
