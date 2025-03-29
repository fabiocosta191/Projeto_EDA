/**
 * @file main.c
 * @brief Programa principal para manipulação de antenas e detecção de nefastos.
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
  * @brief Função principal do programa.
  *
  * Esta função é responsável por:
  * - Ler a lista de antenas de um arquivo.
  * - Apresentar a matriz e a lista de antenas.
  * - Detetar nefastos na matriz.
  * - Inserir e remover antenas da matriz.
  * - Liberar a memória alocada para as listas de antenas e nefastos.
  *
  * @return int Retorna 0 se o programa for executado com sucesso.
  */
int main() {
    char matriz[MAX_LINHAS][MAX_COLUNAS]; /**< Matriz para armazenar dados do arquivo */
    int linhas, colunas; /**< Variáveis para armazenar o número de linhas e colunas da matriz */

    // Ler Lista de antenas do arquivo
    ANT* lista = LerLista("antenas.txt", matriz, &linhas, &colunas); /**< Lista de antenas lida do arquivo */

    //----------------------------------------------
    // Apresentar a matriz e a lista de antenas
    printf("Matriz Lida do Arquivo:\n");
    apresentarMatriz(matriz, linhas, colunas); /**< Apresenta a matriz lida do arquivo */
    apresentarLista(lista); /**< Apresenta a lista de antenas */
    printf("--------------------\n\n\n");

    //----------------------------------------------
    // Detetar Nefastos na matriz
    char matrizNef[MAX_LINHAS][MAX_COLUNAS]; /**< Matriz para armazenar dados com nefastos */
    igualarMatrizes(matrizNef, matriz, linhas, colunas); /**< Copia os dados da matriz original para a matriz de nefastos */
    printf("Matriz Com Nefastos:\n");
    NEF* listaNef = matrizNefastos(matrizNef, linhas, colunas); /**< Insere nefastos na matriz e devolve a lista de nefastos */
    apresentarMatriz(matrizNef, linhas, colunas); /**< Apresenta a matriz com nefastos */
    apresentarListaNef(listaNef); /**< Apresenta a lista de nefastos */
    printf("--------------------\n\n\n");

    //----------------------------------------------
    // Inserir Antena na matriz e na lista de antenas
    printf("Inserir Antena:\tFrequencia: \'C\'\tCoordenadas: (2,2)\n");
    atualizarMatriz(&lista, 'C', 2, 2, matriz); /**< Insere uma antena na matriz e na lista de antenas */
    apresentarMatriz(matriz, linhas, colunas); /**< Apresenta a matriz atualizada */
    apresentarLista(lista); /**< Apresenta a lista de antenas atualizada */

    printf("\n\n\Inserir Antena:\tFrequencia: \'C\'\tCoordenadas: (4,6)\n");
    atualizarMatriz(&lista, 'C', 4, 6, matriz); /**< Insere outra antena na matriz e na lista de antenas */
    apresentarMatriz(matriz, linhas, colunas); /**< Apresenta a matriz atualizada */
    apresentarLista(lista); /**< Apresenta a lista de antenas atualizada */
    printf("--------------------\n\n\n");
    
    //----------------------------------------------
    // Detetar Nefastos na matriz
    char matrizNef2[MAX_LINHAS][MAX_COLUNAS]; /**< Matriz para armazenar dados com nefastos */
    igualarMatrizes(matrizNef2, matriz, linhas, colunas); /**< Copia os dados da matriz original para a matriz de nefastos */
    printf("Matriz Com Nefastos com a adicao da frequencia C:\n");
    NEF* listaNef2 = matrizNefastos(matrizNef2, linhas, colunas); /**< Insere nefastos na matriz e devolve a lista de nefastos */
    apresentarMatriz(matrizNef2, linhas, colunas); /**< Apresenta a matriz com nefastos */
    apresentarListaNef(listaNef2); /**< Apresenta a lista de nefastos */
    printf("--------------------\n\n\n");
    
    //----------------------------------------------
    // Remover Antena da matriz e da lista de antenas
	printf("Remover Antena:\tCoordenadas: (2,2)\n");
    removerAntena(&lista, 2, 2, matriz); /**< Remove uma antena da matriz e da lista de antenas */
    apresentarMatriz(matriz, linhas, colunas); /**< Apresenta a matriz atualizada */
    apresentarLista(lista); /**< Apresenta a lista de antenas atualizada */

    // Liberar memória alocada para as listas de antenas e nefastos
    ANT* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->proxAntena;
        free(temp); /**< Libera a memória alocada para a lista de antenas */
    }

    NEF* tempNef;
    while (listaNef != NULL) {
        tempNef = listaNef;
        listaNef = listaNef->proxNef;
        free(tempNef); /**< Libera a memória alocada para a lista de nefastos */
    }

	NEF* tempNef2;
	while (listaNef2 != NULL) {
		tempNef2 = listaNef2;
		listaNef2 = listaNef2->proxNef;
		free(tempNef2); /**< Libera a memória alocada para a lista de nefastos */
	}

    return 0; /**< Retorna 0 indicando que o programa foi executado com sucesso */
}