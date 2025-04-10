/**
 * @file main.c
 * @brief Programa principal para manipulação de antenas e detecção de nefastos.
 * @author Fábio Rafael Gomes Costa
 * @contact a22997@alunos.ipca.pt
 * @course Engenharia Sistemas Informáticos
 * @version "Com correções pos defesa"
 * @date 04/04/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"


 /**
  * @brief Função principal do programa
  *
  * Esta função demonstra o funcionamento do sistema de gestão de antenas e posições nefastas,
  * incluindo operações de leitura, remoção e adição de antenas, além da deteção de interferências.
  *
  * @return int Retorna 0 em caso de sucesso, 1 em caso de erro
  */
int main()
{
    int linhas, colunas;
	Ant* lista = NULL;
    Nef* listaNef = NULL;


    // 1. Leitura do ficheiro e criação da lista de antenas
    AntNef* listaAntNef = LerLista("antenas", ".txt", &linhas, &colunas);
    lista = listaAntNef->lista;
    listaNef = listaAntNef->listaNef;

    // 2. Apresentação dos dados iniciais
    printf("=== DADOS INICIAIS ===\n");
    int printLista = ApresentarLista(lista);
    printf("\n");
    int printMatriz = ApresentarMatrizLista(lista, linhas, colunas);
    // 3. Deteção de posições nefastas
    printf("\n\n=== POSIÇÕES NEFASTAS DETETADAS ===\n");
    int printListaNef = ApresentarListaNef(listaNef);
    printf("\n");
    int printMatrizNef = ApresentarMatrizListaNef(lista, linhas, colunas, listaNef);
    
    lista = listaAntNef->lista;
    listaNef = listaAntNef->listaNef;

    // 5. Demonstração de remoção de antena
    printf("\n--- Após remoção da antena em (6,5) ---\n");
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

    // 6. Demonstração de adição de antena
    printf("\n\n--- Após adição de antena 'A' em (6,5) ---\n");
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

    // 7. Libertação de memória
    printf("\n\n=== LIBERTAÇÃO DE MEMÓRIA ===\n");

    int freeListaAntNef = FreeAntNef(listaAntNef);

    printf("Programa concluído com sucesso.\n");
    return 0;
}