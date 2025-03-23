/**
 * @file funcao.c
 * @brief Implementação de funções para manipulação de antenas e nefastos.
 * @author Fábio Rafael Gomes Costa
 * @contact a22997@alunos.ipca.pt
 * @course Engenharia Sistemas Informáticos
 * @date 18/03/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"

 /**
  * @brief Lê uma lista de antenas a partir de um arquivo e preenche uma matriz.
  *
  * Esta função lê um arquivo contendo dados de antenas, armazena os dados em uma matriz
  * e cria uma lista encadeada de antenas.
  *
  * @param nomeFicheiro Nome do arquivo a ser lido.
  * @param matriz Matriz onde os dados serão armazenados.
  * @param linhas Ponteiro para armazenar o número de linhas da matriz.
  * @param colunas Ponteiro para armazenar o número de colunas da matriz.
  * @return ANT* Retorna a lista de antenas lida do arquivo.
  */
ANT* LerLista(const char* nomeFicheiro, char matriz[MAX_LINHAS][MAX_COLUNAS], int* linhas, int* colunas) {
    FILE* ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL) {
        perror("Erro ao abrir o ficheiro");
        return NULL;
    }

    ANT* lista = NULL;
    char linha[MAX_COLUNAS];
    int y = 0;
    int maxColunas = 0;

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
            matriz[y][x] = linha[x]; // Armazena na matriz
            if (linha[x] != '.') {
                inserirAntena(&lista, linha[x], x, y);
            }
        }

        // Preencher com '.' os espaços não usados
        for (int x = tamLinha; x < MAX_COLUNAS; x++) {
            matriz[y][x] = '.';
        }
        y++;
    }

    *linhas = y;
    *colunas = maxColunas;
    fclose(ficheiro);
    return lista;
}

/**
 * @brief Insere uma nova antena na lista de antenas.
 *
 * @param lista Ponteiro para a lista de antenas.
 * @param freq Frequência da antena.
 * @param x Coordenada x da antena.
 * @param y Coordenada y da antena.
 */
void inserirAntena(ANT** lista, char freq, int x, int y) {
    ANT* novaAntena = (ANT*)malloc(sizeof(ANT));
    if (novaAntena == NULL) {
        perror("Erro ao alocar memória");
        return;
    }
    novaAntena->freqAntena = freq;
    novaAntena->x = x;
    novaAntena->y = y;
    novaAntena->proxAntena = *lista;
    *lista = novaAntena;
}

/**
 * @brief Apresenta a lista de antenas.
 *
 * @param lista Lista de antenas a ser apresentada.
 */
void apresentarLista(ANT* lista) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return;
    }
    printf("\nLista de Antenas:\n");
    while (lista != NULL) {
        printf("Antena: %c | Coordenadas: (%d, %d)\n", lista->freqAntena, lista->x, lista->y);
        lista = lista->proxAntena;
    }
}

/**
 * @brief Apresenta a matriz.
 *
 * @param matriz Matriz a ser apresentada.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 */
void apresentarMatriz(char matriz[MAX_LINHAS][MAX_COLUNAS], int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Copia os dados de uma matriz para outra.
 *
 * @param matrizNef Matriz de destino.
 * @param matriz Matriz de origem.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 */
void igualarMatrizes(char matrizNef[MAX_LINHAS][MAX_COLUNAS], char matriz[MAX_LINHAS][MAX_COLUNAS], int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        memcpy(matrizNef[i], matriz[i], colunas * sizeof(char));
    }
}

/**
 * @brief Detecta e insere nefastos na matriz.
 *
 * Esta função percorre a matriz e insere nefastos ('#') em posições específicas
 * com base nas coordenadas das antenas.
 *
 * @param matriz Matriz onde os nefastos serão inseridos.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 * @return NEF* Retorna a lista de nefastos detectados.
 */
NEF* matrizNefastos(char matriz[MAX_LINHAS][MAX_COLUNAS], int linhas, int colunas) {
    int menorx, menory, maiorx, maiory, difx, dify;
    NEF* lista = NULL;
    for (int y = 0; y < linhas; y++) {
        for (int x = 0; x < colunas; x++) {
            if (matriz[y][x] != '.' && matriz[y][x] != '#') {
                for (int y2 = 0; y2 < linhas; y2++) {
                    for (int x2 = 0; x2 < colunas; x2++) {
                        if (matriz[y][x] == matriz[y2][x2] && (y != y2 || x != x2)) {

                            if (x > x2)
                            {
                                difx = x - x2;
                                menorx = x2 - difx;
                                maiorx = x + difx;
                            }
                            else
                            {
                                difx = x2 - x;
                                menorx = x - difx;
                                maiorx = x2 + difx;
                            }
                            if (y > y2)
                            {
                                dify = y - y2;
                                menory = y2 - dify;
                                maiory = y + dify;
                            }
                            else
                            {
                                dify = y2 - y;
                                menory = y - dify;
                                maiory = y2 + dify;
                            }
                            if (x > x2 && y > y2 || x < x2 && y < y2)
                            {
                                if (matriz[menory][menorx] == '.' && menorx >= 0 && menory >= 0)
                                {
                                    matriz[menory][menorx] = '#';
                                    inserirNefasto(&lista, menorx, menory);
                                }
                                if (matriz[maiory][maiorx] == '.' && maiorx <= colunas && maiory <= linhas)
                                {
                                    matriz[maiory][maiorx] = '#';
                                    inserirNefasto(&lista, maiorx, maiory);
                                }
                            }
                            else if (x > x2 && y < y2 || x<x2 && y>y2)
                            {
                                if (matriz[menory][maiorx] == '.' && menorx >= 0 && menory >= 0)
                                {
                                    matriz[menory][maiorx] = '#';
                                    inserirNefasto(&lista, maiorx, menory);
                                }
                                if (matriz[maiory][menorx] == '.' && maiorx <= colunas && maiory <= linhas)
                                {
                                    matriz[maiory][menorx] = '#';
                                    inserirNefasto(&lista, menorx, maiory);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return lista;
}

/**
 * @brief Insere um nefasto na lista de nefastos.
 *
 * @param lista Ponteiro para a lista de nefastos.
 * @param x Coordenada x do nefasto.
 * @param y Coordenada y do nefasto.
 */
void inserirNefasto(NEF** lista, int x, int y) {
    NEF* novoNefasto = (NEF*)malloc(sizeof(NEF));
    if (novoNefasto == NULL) {
        perror("Erro ao alocar memória");
        return;
    }

    novoNefasto->x = x;
    novoNefasto->y = y;
    novoNefasto->proxNef = *lista;
    *lista = novoNefasto;
}

/**
 * @brief Apresenta a lista de nefastos.
 *
 * @param lista Lista de nefastos a ser apresentada.
 */
void apresentarListaNef(NEF* lista) {
    if (lista == NULL) {
        printf("Lista vazia\n");
        return;
    }

    printf("\nLista de Nefastos:\n");
    while (lista != NULL) {
        printf("Nefastos Coordenadas: (%d, %d)\n", lista->x, lista->y);
        lista = lista->proxNef;
    }
}

/**
 * @brief Atualiza a matriz e a lista de antenas com uma nova antena.
 *
 * @param lista Ponteiro para a lista de antenas.
 * @param freq Frequência da antena.
 * @param x Coordenada x da antena.
 * @param y Coordenada y da antena.
 * @param matriz Matriz a ser atualizada.
 */
void atualizarMatriz(ANT** lista, char freq, int x, int y, char matriz[MAX_LINHAS][MAX_COLUNAS])
{
    ANT* temp = *lista;
    while (temp != NULL)
    {
        if (temp->x == x && temp->y == y)
        {
            matriz[y][x] = freq;
            return;
        }
        temp = temp->proxAntena;
    }
    inserirAntena(lista, freq, x, y);
    matriz[y][x] = freq;
}

/**
 * @brief Remove uma antena da lista e da matriz.
 *
 * @param lista Ponteiro para a lista de antenas.
 * @param x Coordenada x da antena.
 * @param y Coordenada y da antena.
 * @param matriz Matriz a ser atualizada.
 */
void removerAntena(ANT** lista, int x, int y, char matriz[MAX_LINHAS][MAX_COLUNAS])
{
    ANT* temp = *lista;
    ANT* anterior = NULL;
    while (temp != NULL)
    {
        if (temp->x == x && temp->y == y)
        {
            if (anterior == NULL)
            {
                *lista = temp->proxAntena;
            }
            else
            {
                anterior->proxAntena = temp->proxAntena;
            }
            matriz[y][x] = '.';
            free(temp);
            return;
        }
        anterior = temp;
        temp = temp->proxAntena;
    }
}