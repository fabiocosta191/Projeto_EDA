#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"


int main() {
    Grafo grafo;
    Ant* listaAntenas = NULL;
    int linhas = 0, colunas = 0;
	int validacaoResultado = 0;

    // Substitui "matriz" e ".txt" pelos nomes reais do teu ficheiro
	listaAntenas = LerLista("antenas", ".txt", &linhas, &colunas, &grafo);//não é necessario returnar a lista
    if (listaAntenas == NULL) {
        perror("Erro ao carregar a lista de antenas.\n");
        return 1;
    }


    validacaoResultado = ImprimirMatriz(&grafo, linhas, colunas);
	if (validacaoResultado != 200) {
        perror("Erro ao imprimir a matriz.\n");
	}
    validacaoResultado = ListarArestasENefastos(&grafo, linhas, colunas);
    if (validacaoResultado != 200) {
        perror("Erro ao imprimir lista.\n");
    }
    validacaoResultado = IniciarDFS(&grafo, 3); //Inicia DFS a partir da antena com ID 3 (ajusta conforme necessário)
    if (validacaoResultado != 200) {
        perror("Erro na procura em profundidade.\n");
    }
    validacaoResultado = BFS(&grafo, 3);
    if (validacaoResultado != 200) {
        perror("Erro na procura em largura.\n");
    }
    validacaoResultado = TodosCaminhos(&grafo, 1, 6);
    if (validacaoResultado != 200) {
        perror("Erro na procura ao encontrar o caminho.\n");
    }
    

	// Liberta a memória alocada
    FreeListaAntenas(listaAntenas, &grafo);
    if (validacaoResultado != 200) {
        perror("Erro ao libertar memoria.\n");
    }
	else 
    {
		printf("Memoria libertada com sucesso.\n");
	}
    return 0;
}
