/**
 * @file main.c
 * @brief Programa principal para manipula��o de antenas e detec��o de nefastos.
 * @author F�bio Rafael Gomes Costa
 * @contact a22997@alunos.ipca.pt
 * @course Engenharia Sistemas Inform�ticos
 * @version "Com corre��es pos defesa"
 * @date 04/04/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"


 /**
  * @brief Fun��o principal do programa
  *
  * Esta fun��o demonstra o funcionamento do sistema de gest�o de antenas e posi��es nefastas,
  * incluindo opera��es de leitura, remo��o e adi��o de antenas, al�m da dete��o de interfer�ncias.
  *
  * @return int Retorna 0 em caso de sucesso, 1 em caso de erro
  */
int main()
{
    int linhas, colunas;
	Ant* lista = NULL;
    Nef* listaNef = NULL;


    // 1. Leitura do ficheiro e cria��o da lista de antenas
    AntNef* listaAntNef = LerLista("antenas", ".txt", &linhas, &colunas);
    lista = listaAntNef->lista;
    listaNef = listaAntNef->listaNef;

    // 2. Apresenta��o dos dados iniciais
    printf("=== DADOS INICIAIS ===\n");
    int printLista = ApresentarLista(lista);
    printf("\n");
    int printMatriz = ApresentarMatrizLista(lista, linhas, colunas);
    // 3. Dete��o de posi��es nefastas
    printf("\n\n=== POSI��ES NEFASTAS DETETADAS ===\n");
    int printListaNef = ApresentarListaNef(listaNef);
    printf("\n");
    int printMatrizNef = ApresentarMatrizListaNef(lista, linhas, colunas, listaNef);
    
    lista = listaAntNef->lista;
    listaNef = listaAntNef->listaNef;

    // 5. Demonstra��o de remo��o de antena
    printf("\n--- Ap�s remo��o da antena em (6,5) ---\n");
    listaAntNef = RemoverAntena(listaAntNef, 6, 5);
    lista = listaAntNef->lista;
    listaNef = listaAntNef->listaNef;

    printLista = ApresentarLista(lista);
    printf("\n");
    printMatriz = ApresentarMatrizLista(lista, linhas, colunas);
    printf("\n");
    printListaNef = ApresentarListaNef(listaNef);
    printf("\n");
    printMatrizNef = ApresentarMatrizListaNef(lista, linhas, colunas, listaNef);

    // 6. Demonstra��o de adi��o de antena
    printf("\n\n--- Ap�s adi��o de antena 'A' em (6,5) ---\n");
    listaAntNef = AdicionarAntena(listaAntNef, 'A', 6, 5, linhas, colunas);
    lista = listaAntNef->lista;
    listaNef = listaAntNef->listaNef;

    printLista = ApresentarLista(lista);
    printf("\n");
    printMatriz = ApresentarMatrizLista(lista, linhas, colunas);
    printf("\n");
    printListaNef = ApresentarListaNef(listaNef);
    printf("\n");
    printMatrizNef = ApresentarMatrizListaNef(lista, linhas, colunas, listaNef);

    // 7. Liberta��o de mem�ria
    printf("\n\n=== LIBERTA��O DE MEM�RIA ===\n");

    int freeListaAntNef = FreeAntNef(listaAntNef);

    printf("Programa conclu�do com sucesso.\n");
    return 0;
}