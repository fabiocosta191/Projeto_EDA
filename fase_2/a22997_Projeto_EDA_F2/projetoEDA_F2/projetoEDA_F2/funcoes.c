/**
 * @file funcao.c
 * @brief Implementa��o de funcoes para manipulacao de antenas e nefastos.
 * @author Fabio Rafael Gomes Costa
 * @contact a22997@alunos.ipca.pt
 * @course Engenharia Sistemas Informaticos
 * @date 04/04/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


Ant* LerLista(const char* nomeFicheiro, const char* tipoFicheiro, int* linhas, int* colunas, Grafo* grafo) {
    FILE* ficheiro;
    char nomeCompleto[256];  // Buffer para o nome do arquivo
    snprintf(nomeCompleto, sizeof(nomeCompleto), "%s%s", nomeFicheiro, tipoFicheiro);

    if (strcmp(tipoFicheiro, ".txt") == 0) {
        errno_t err = fopen_s(&ficheiro, nomeCompleto, "r");
        if (err != 0) {
            perror("Erro ao abrir o ficheiro");
            return NULL;
        }
    }
    else {
        errno_t err = fopen_s(&ficheiro, nomeCompleto, "rb");
        if (err != 0) {
            perror("Erro ao abrir o ficheiro");
            return NULL;
        }
    }

    // Já recebido como argumento
    memset(grafo->Antena, 0, sizeof(grafo->Antena)); // Limpa ponteiros
	//grafo->Antena[0] = NULL; // Inicializa o primeiro elemento como NULL caso id comece a 1, o [0] deve ser null

    Ant* lista = NULL;
    char linha[MAX_COLUNAS];//100
    int y = 0;
    int maxColunas = 0;
    int id = 0; // Inicializa o ID da antena

    while (fgets(linha, sizeof(linha), ficheiro)) {
        int tamLinha = strlen(linha);
        if (linha[tamLinha - 1] == '\n') {
            linha[tamLinha - 1] = '\0'; // Remover quebra de linha
            tamLinha--;
        }
        if (tamLinha > maxColunas) {
            maxColunas = tamLinha;
        }
        for (int x = 0; x < tamLinha; x++) {
            if (linha[x] != '.') {
                lista = InserirAntena(lista, grafo, linha[x], x, y, id);
                id++; // Incrementa o ID da antena
            }
        }
        y++;
    }

    *linhas = y;
    *colunas = maxColunas;
    /*Nef* listaNef = EncontrarNefastos(lista, y, maxColunas);

    AntNef* listaAntNef = (AntNef*)malloc(sizeof(AntNef));
    if (listaAntNef == NULL) {
        perror("Erro ao alocar mem�ria para AntNef");
        FreeLista(lista);
        FreeListaNef(listaNef);
        return 1;
    }
    listaAntNef->lista = lista;
    listaAntNef->listaNef = listaNef;*/
    int verificaArestas=CriarListaArestas(lista);
	if (verificaArestas == 0) {
		perror("Erro ao criar lista de arestas");
		fclose(ficheiro);
		return NULL;
	}
    fclose(ficheiro);
    return lista;
}


Ant* InserirAntena(Ant* lista, Grafo* grafo, char freq, int x, int y, int id) {
    Ant* novaAntena = (Ant*)malloc(sizeof(Ant));
    if (novaAntena == NULL) {
        perror("Erro ao alocar memória para antena");
        return lista;
    }

    novaAntena->freqAntena = freq;
    novaAntena->x = x;
    novaAntena->y = y;
    novaAntena->id = id;
    novaAntena->proxAntena = lista;
    novaAntena->listaAresta = NULL;

    if (grafo != NULL && id < MAX_VERTICES) {
        grafo->Antena[id] = novaAntena;
    }

    return novaAntena;
}


int CriarListaArestas(Ant* lista) {
    
    Ant* listaAnt1 = lista;
    while (listaAnt1 != NULL) {
        Ant* listaAnt2 = lista;

        while (listaAnt2 != NULL) {

            if (listaAnt1->freqAntena == listaAnt2->freqAntena && (listaAnt1->y != listaAnt2->y || listaAnt1->x != listaAnt2->x)) {
				Ars* novaAresta = (Ars*)malloc(sizeof(Ars));
				if (novaAresta == NULL) {
					perror("Erro ao alocar mem�ria para a aresta");
					return 0;
				}
				novaAresta->destinoAntena = listaAnt2;
				novaAresta->proximaAresta = listaAnt1->listaAresta;
				listaAnt1->listaAresta = novaAresta;
            }
            listaAnt2 = listaAnt2->proxAntena;
        }
        listaAnt1 = listaAnt1->proxAntena;
    }
	return 1;

}




//* Função para liberar a memória alocada para a lista de antenas, grafo, vertice */
int FreeListaAntenas(Ant* lista) {
    Ant* atual = lista;
    while (atual != NULL) {
        Ars* aresta = atual->listaAresta;
        // Liberta todas as arestas desta antena
        while (aresta != NULL) {
            Ars* tempAresta = aresta;
            aresta = aresta->proximaAresta;
            free(tempAresta);
        }

        Ant* tempAntena = atual;
        atual = atual->proxAntena;
        free(tempAntena);
    }
	return 1;
}

int FreeGrafo(Grafo* grafo) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        grafo->Antena[i] = NULL; // só para segurança se não fores libertar aqui
    }
	free(grafo); // Liberta a memória alocada para o grafo
	return 1;
}



