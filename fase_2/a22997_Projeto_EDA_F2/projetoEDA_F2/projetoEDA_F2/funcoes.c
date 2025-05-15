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

#pragma region Leitura_Armazenamento
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

    int verificaArestas = CriarListaArestas(lista, y, maxColunas);
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

int CriarListaArestas(Ant* lista, int linhas, int colunas) {
    int menorx, menory, maiorx, maiory, difx, dify, idant1, idant2;
    Ant* listaAnt1 = lista;
    while (listaAnt1 != NULL) {
        Ant* listaAnt2 = lista;

        while (listaAnt2 != NULL) {

            if (listaAnt1->freqAntena == listaAnt2->freqAntena && (listaAnt1->y != listaAnt2->y || listaAnt1->x != listaAnt2->x)) {
                Ars* novaAresta = (Ars*)malloc(sizeof(Ars));
                if (novaAresta == NULL) {
                    perror("Erro ao alocar memoria para a aresta");
                    return 500;
                }
                novaAresta->origemAntena = listaAnt1;
                novaAresta->destinoAntena = listaAnt2;
                novaAresta->proximaAresta = listaAnt1->listaAresta;
                listaAnt1->listaAresta = novaAresta;

                if (listaAnt1->y != listaAnt2->y || listaAnt1->x != listaAnt2->x){
                    if (listaAnt1->x > listaAnt2->x)
                    {
                        difx = listaAnt1->x - listaAnt2->x;
                        menorx = listaAnt2->x - difx;
                        maiorx = listaAnt1->x + difx;
                    }
                    else
                    {
                        difx = listaAnt2->x - listaAnt1->x;
                        menorx = listaAnt1->x - difx;
                        maiorx = listaAnt2->x + difx;
                    }
                    if (listaAnt1->y > listaAnt2->y)
                    {
                        dify = listaAnt1->y - listaAnt2->y;
                        menory = listaAnt2->y - dify;
                        maiory = listaAnt1->y + dify;
                    }
                    else
                    {
                        dify = listaAnt2->y - listaAnt1->y;
                        menory = listaAnt1->y - dify;
                        maiory = listaAnt2->y + dify;
                    }

                    idant1 = listaAnt1->id;
                    idant2 = listaAnt2->id;

                    if (listaAnt1->x > listaAnt2->x && listaAnt1->y > listaAnt2->y || listaAnt1->x < listaAnt2->x && listaAnt1->y < listaAnt2->y)
                    {
                        if (listaAnt1->y < listaAnt2->y) {
                            if (menorx >= 0 && menory >= 0 && menorx <= linhas && menory <= colunas)
                            {
                                novaAresta->xNef = menorx;
                                novaAresta->yNef = menory;
                            }
                        }
                        else {
                            if (maiorx <= colunas && maiory <= linhas && maiorx <= linhas && maiory <= colunas)
                            {
                                novaAresta->xNef = maiorx;
                                novaAresta->yNef = maiory;
                            }
                        }
                    }
                    else if (listaAnt1->x > listaAnt2->x && listaAnt1->y < listaAnt2->y || listaAnt1->x < listaAnt2->x && listaAnt1->y > listaAnt2->y)
                    {
                        if (listaAnt1->y < listaAnt2->y) {

                            if (maiorx >= 0 && menory >= 0 && maiorx <= linhas && menory <= colunas)
                            {
                                novaAresta->xNef = maiorx;
                                novaAresta->yNef = menory;
                            }
                        }
                        else {
                            if (menorx <= colunas && maiory <= linhas && menorx <= linhas && maiory <= colunas)
                            {
                                novaAresta->xNef = menorx;
                                novaAresta->yNef = maiory;
                            }

                        }
                    }
                }
            }
            listaAnt2 = listaAnt2->proxAntena;
        }
        listaAnt1 = listaAnt1->proxAntena;
    }
    return 200;

}

#pragma endregion


#pragma region DFS
int DFS(Ant* atual, int visitado[], int idOrigem) {
    if (atual == NULL || visitado[atual->id]) {
        return 200;
    }

    visitado[atual->id] = 1;

    if (idOrigem == -1) {
        printf("Antena %d (%c) em [%d, %d] (Origem)\n",
            atual->id, atual->freqAntena, atual->x, atual->y);
    }
    else {
        printf("Antena %d (%c) em [%d, %d] (Aresta: origem %d -> destino %d)\n",
            atual->id, atual->freqAntena, atual->x, atual->y, idOrigem, atual->id);
    }

    Ars* aresta = atual->listaAresta;
    while (aresta != NULL) {
        DFS(aresta->destinoAntena, visitado, atual->id);
        aresta = aresta->proximaAresta;
    }
    return 200;
}

int IniciarDFS(Grafo* grafo, int idOrigem) {
    if (idOrigem < 0 || idOrigem >= MAX_VERTICES || grafo->Antena[idOrigem] == NULL) {
        fprintf(stderr, "Antena com ID %d não existe.\n", idOrigem);
        return 500;
    }

    int visitado[MAX_VERTICES] = { 0 };
    printf("DFS a partir da antena %d:\n", idOrigem);
    DFS(grafo->Antena[idOrigem], visitado, -1);  // -1 = raiz
    printf("\n\n");
    return 200;
}
#pragma endregion


#pragma region BFS
int BFS(Grafo* grafo, int idOrigem) {
    if (grafo->Antena[idOrigem] == NULL) {
        printf("Antena com ID %d não existe.\n", idOrigem);
        return 200;
    }

    int visitado[MAX_VERTICES] = { 0 };
    int fila[MAX_VERTICES];
    int origem[MAX_VERTICES];  // Guarda de onde veio cada antena

    int frente = 0, tras = 0;
    fila[tras] = idOrigem;
    origem[tras] = -1;
    visitado[idOrigem] = 1;

    printf("BFS a partir da antena %d:\n", idOrigem);

    while (frente <= tras) {
        int atualID = fila[frente];
        int origemID = origem[frente];
        frente++;

        Ant* atual = grafo->Antena[atualID];

        if (origemID == -1) {
            printf("Antena %d (%c) em [%d, %d] (Origem)\n",
                atual->id, atual->freqAntena, atual->x, atual->y);
        }
        else {
            printf("Antena %d (%c) em [%d, %d] (Aresta: origem %d -> destino %d)\n",
                atual->id, atual->freqAntena, atual->x, atual->y, origemID, atualID);
        }

        Ars* aresta = atual->listaAresta;
        while (aresta != NULL) {
            int vizinhoID = aresta->destinoAntena->id;
            if (!visitado[vizinhoID]) {
                tras++;
                fila[tras] = vizinhoID;
                origem[tras] = atualID;
                visitado[vizinhoID] = 1;
            }
            aresta = aresta->proximaAresta;
        }
    }
    printf("\n\n");
    return 200;
}
#pragma endregion


#pragma region Todos_Caminhos
int EncontrarCaminhos(Ant* atual, int idDestino, int visitado[], int caminho[], int posicao) {
    if (atual == NULL) return 200;

    visitado[atual->id] = 1;
    caminho[posicao++] = atual->id;

    if (atual->id == idDestino) {
        for (int i = 0; i < posicao; i++) {
            printf("%d", caminho[i]);
            if (i < posicao - 1) printf(" -> ");
        }
        printf("\n");
    }
    else {
        Ars* aresta = atual->listaAresta;
        while (aresta != NULL) {
            int vizinhoID = aresta->destinoAntena->id;
            if (!visitado[vizinhoID]) {
                EncontrarCaminhos(aresta->destinoAntena, idDestino, visitado, caminho, posicao);
            }
            aresta = aresta->proximaAresta;
        }
    }

    visitado[atual->id] = 0; // backtracking
	return 200;
}
int TodosCaminhos(Grafo* grafo, int idOrigem, int idDestino) {
    if (grafo->Antena[idOrigem] == NULL || grafo->Antena[idDestino] == NULL) {
        printf("Antena(s) inválida(s)\n");
        return 200;
    }

    int visitado[MAX_VERTICES] = { 0 };
    int caminho[MAX_VERTICES];
    printf("Todos os caminhos de %d para %d:\n", idOrigem, idDestino);
    //compara a frequencia da antena origem e destino
    if (grafo->Antena[idOrigem]->freqAntena != grafo->Antena[idDestino]->freqAntena) {
        printf("As antenas de origem e destino nao tem a mesma frequencia.\n\n\n");
        return 200;
    }
    EncontrarCaminhos(grafo->Antena[idOrigem], idDestino, visitado, caminho, 0);
    printf("\n\n");
    return 200;

}
#pragma endregion
















#pragma region Libertacao_Memoria

int FreeListaAntenas(Ant* lista, Grafo* grafo) {
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
    for (int i = 0; i < MAX_VERTICES; i++) {
        grafo->Antena[i] = NULL;
    }

    return 200;
}

#pragma endregion




