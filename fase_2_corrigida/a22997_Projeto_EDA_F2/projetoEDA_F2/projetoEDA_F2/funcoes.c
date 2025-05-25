/**
 * @file funcao.c
 * @brief Implementação das funções para manipulação de antenas, grafos e zonas nefastas.
 *
 * Inclui as operações de leitura, criação de grafos com lista de adjacência, travessias (DFS, BFS),
 * descoberta de caminhos possíveis entre antenas, exportação de dados e libertação de memória.
 *
 * @author Fábio Rafael Gomes Costa
 * @date 18/05/2025
 * @version 1.0
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

#pragma region Leitura_Armazenamento
 /**
  * @brief Lê uma matriz de antenas a partir de um ficheiro (.txt ou .bin) e constrói o grafo.
  *
  * A função percorre o ficheiro linha a linha e cria uma estrutura ligada (lista + grafo) com as antenas.
  * Após a leitura, também estabelece as conexões entre antenas de mesma frequência.
  *
  * @param nomeFicheiro Nome base do ficheiro (sem extensão)
  * @param tipoFicheiro Extensão do ficheiro (".txt" ou ".bin")
  * @param linhas Ponteiro para armazenar o número de linhas lidas
  * @param colunas Ponteiro para armazenar o número de colunas lidas
  * @return Ponteiro para a estrutura do grafo construído, ou NULL em caso de erro
  */
Grafo* LerLista(const char* nomeFicheiro, const char* tipoFicheiro, int* linhas, int* colunas) {
    FILE* ficheiro;
    char nomeCompleto[256];  // Buffer para o nome do arquivo
    snprintf(nomeCompleto, sizeof(nomeCompleto), "%s%s", nomeFicheiro, tipoFicheiro);
    if (strcmp(tipoFicheiro, ".txt") == 0) {
        errno_t err = fopen_s(&ficheiro, nomeCompleto, "r");
        if (err != 0) {
            return NULL;
        }
    }
    else {
        errno_t err = fopen_s(&ficheiro, nomeCompleto, "rb");
        if (err != 0) {
            return NULL;
        }
    }


    Grafo* grafo = NULL;
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
                lista = CriarAntena(lista, linha[x], x, y, id);
				grafo = InserirAntena(grafo, lista);
                id++; // Incrementa o ID da antena
            }
        }
        y++;
    }


    *linhas = y;
    *colunas = maxColunas;

    int verificaArestas = CriarListaArestas(grafo, y, maxColunas);
	if (verificaArestas != 200) {
		fclose(ficheiro);
		return NULL;
	}


    fclose(ficheiro);
    return grafo;
}

/**
 * @brief Cria uma nova antena e insere-a no topo da lista ligada.
 *
 * @param lista Lista atual de antenas
 * @param freq Frequência da antena (carácter)
 * @param x Posição X na matriz
 * @param y Posição Y na matriz
 * @param id Identificador único da antena
 * @return Ponteiro para a nova cabeça da lista
 */
Ant* CriarAntena(Ant* lista, char freq, int x, int y, int id) {
    Ant* novaAntena = (Ant*)malloc(sizeof(Ant));
    if (novaAntena == NULL) {
        return lista;
    }

    novaAntena->freqAntena = freq;
    novaAntena->x = x;
    novaAntena->y = y;
    novaAntena->id = id;
    novaAntena->proxAntena = lista;
    novaAntena->listaAresta = NULL;

    return novaAntena;
}

/**
 * @brief Insere uma antena na estrutura do grafo (lista encadeada de grafos).
 *
 * @param grafo Estrutura atual do grafo
 * @param lista Ponteiro para a nova antena a ser inserida
 * @return Ponteiro atualizado para o grafo
 */
Grafo* InserirAntena(Grafo* grafo, Ant* lista) {
	Grafo* novoGrafo = (Grafo*)malloc(sizeof(Grafo));
	if (novoGrafo == NULL) {
		return NULL;
	}

	novoGrafo->Antena = lista;
	novoGrafo->listaGrafo = grafo;

	return novoGrafo;
}

/**
 * @brief Cria ligações (arestas) entre antenas com a mesma frequência e identifica zonas nefastas.
 *
 * @param grafo Grafo com a lista de antenas
 * @param linhas Número total de linhas da matriz
 * @param colunas Número total de colunas da matriz
 * @return 200 em caso de sucesso, 501 em caso de erro de alocação
 */
int CriarListaArestas(Grafo* grafo, int linhas, int colunas) {
    int menorx, menory, maiorx, maiory, difx, dify, idant1, idant2;

    Ant* listaAnt1 = grafo->Antena;
    while (listaAnt1 != NULL) {
        Ant* listaAnt2 = grafo->Antena;

        while (listaAnt2 != NULL) {

            if (listaAnt1->freqAntena == listaAnt2->freqAntena && (listaAnt1->y != listaAnt2->y || listaAnt1->x != listaAnt2->x)) {
                Ars* novaAresta = (Ars*)malloc(sizeof(Ars));
                if (novaAresta == NULL) {
                    return 501;
                }
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
/**
 * @brief Função recursiva que realiza a travessia DFS (Depth-First Search) sobre as antenas.
 *
 * @param atual Antena atual sendo visitada
 * @param visitado Vetor de marcação de antenas visitadas
 * @param idOrigem ID da antena de onde veio
 * @return 200 sempre
 */
int DFS(Ant* atual, int visitado[], int idOrigem) {
    if (atual == NULL || visitado[atual->id]) {
        return 200;
    }

    visitado[atual->id] = 1;

    if (idOrigem == -1) { // Se idOrigem for -1, significa que é a raiz 
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

/**
 * @brief Inicia a travessia DFS a partir de uma antena de origem.
 *
 * @param grafo Grafo contendo todas as antenas
 * @param idOrigem ID da antena inicial
 * @return 200 se bem-sucedido, 500 se ID inválido
 */
int IniciarDFS(Grafo* grafo, int idOrigem) {
	Grafo* grafoAtual = grafo;
	Ant* antena = NULL;

    if (idOrigem < 0 || idOrigem >= MAX_VERTICES) {
        fprintf(stderr, "Antena com ID %d não existe.\n", idOrigem);
        return 500;
    }
	while (grafoAtual != NULL)
	{
        if (grafoAtual->Antena->id == idOrigem)
        {
             antena = grafoAtual->Antena;
        }
		grafoAtual = grafoAtual->listaGrafo;
	}
	if (antena == NULL) {
		return 500;
	}

    int visitado[MAX_VERTICES] = { 0 };
    printf("DFS a partir da antena %d:\n", idOrigem);
    DFS(antena, visitado, -1);  // -1 = raiz
    printf("\n\n");
    return 200;
}
#pragma endregion

#pragma region BFS
/**
 * @brief Executa uma travessia em largura (BFS - Breadth First Search) no grafo.
 *
 * @param grafo Grafo contendo as antenas
 * @param idOrigem ID da antena de origem
 * @return 200 se executado com sucesso, mesmo que a antena não exista
 */
int BFS(Grafo* grafo, int idOrigem) {
    // Procurar a antena com o ID de origem
    Ant* origemAntena = NULL;
    Grafo* aux = grafo;
    while (aux != NULL) {
        if (aux->Antena->id == idOrigem) {
            origemAntena = aux->Antena;
            break;
        }
        aux = aux->listaGrafo;
    }
    if (origemAntena == NULL) {
        printf("Antena com ID %d não existe.\n", idOrigem);
        return 200;
    }
    int visitado[MAX_VERTICES] = { 0 };
    int fila[MAX_VERTICES];
    int origem[MAX_VERTICES];
    int frente = 0, tras = 0;
    fila[tras] = origemAntena->id;
    origem[tras] = -1;
    visitado[origemAntena->id] = 1;
    printf("BFS a partir da antena %d:\n", origemAntena->id);
    while (frente <= tras) {
        int atualID = fila[frente];
        int origemID = origem[frente];
        frente++;
        Ant* atual = NULL;
        Grafo* busca = grafo;
        while (busca != NULL) {
            if (busca->Antena->id == atualID) {
                atual = busca->Antena;
                break;
            }
            busca = busca->listaGrafo;
        }
        if (atual == NULL) continue;
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
                origem[tras] = atual->id;
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
/**
 * @brief Procura recursivamente todos os caminhos possíveis de uma antena até um destino.
 *
 * @param atual Ponteiro para a antena atual no caminho
 * @param idDestino ID da antena destino
 * @param visitado Vetor de marcação de antenas já visitadas
 * @param caminho Vetor de IDs representando o caminho atual
 * @param posicao Posição atual no vetor caminho
 * @return 200 sempre
 */
int EncontrarCaminhos(Ant* atual, int idDestino, int visitado[], int caminho[], int posicao) {
    if (atual == NULL) return 200;
    int verificacao;

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
                verificacao = EncontrarCaminhos(aresta->destinoAntena, idDestino, visitado, caminho, posicao);
            }
            aresta = aresta->proximaAresta;
        }
    }
    visitado[atual->id] = 0; // backtracking
	verificacao = 200;
    return verificacao;
}

/**
 * @brief Lista todos os caminhos possíveis entre duas antenas se tiverem a mesma frequência.
 *
 * @param grafo Grafo com as antenas
 * @param idOrigem ID da antena de origem
 * @param idDestino ID da antena destino
 * @return 200 em caso de sucesso, 500 se IDs inválidos
 */
int TodosCaminhos(Grafo* grafo, int idOrigem, int idDestino) {

    int visitado[MAX_VERTICES] = { 0 };
    int caminho[MAX_VERTICES];
    Grafo* grafoAtual = grafo;
    Ant* antenaOrigem = NULL;
	Ant* antenaDestino = NULL;

    if (idOrigem < 0 || idOrigem >= MAX_VERTICES) {
        fprintf(stderr, "Antena com ID %d não existe.\n", idOrigem);
        return 500;
    }
    while (grafoAtual != NULL)
    {
        if (grafoAtual->Antena->id == idOrigem)
        {
            antenaOrigem = grafoAtual->Antena;
        }
		if (grafoAtual->Antena->id == idDestino)
		{
			antenaDestino = grafoAtual->Antena;
		}
        grafoAtual = grafoAtual->listaGrafo;
    }
    if (antenaOrigem == NULL || antenaDestino == NULL) {
        return 500;
    }


    printf("Todos os caminhos de %d para %d:\n", idOrigem, idDestino);
    //compara a frequencia da antena origem e destino
    if (antenaOrigem->freqAntena != antenaDestino->freqAntena) {
        printf("As antenas de origem e destino nao tem a mesma frequencia.\n\n\n");
        return 200;
    }
    int verificacao = EncontrarCaminhos(antenaOrigem, idDestino, visitado, caminho, 0);
    printf("\n\n");
    return verificacao;
}
#pragma endregion

#pragma region Exportar_Dados

/**
 * @brief Exporta o conteúdo da matriz de antenas para um ficheiro de texto ou binário.
 *
 * @details As posições são preenchidas com o símbolo da antena, ou '.' caso esteja vazia.
 * No caso de exportação binária, os caracteres são gravados diretamente em bytes.
 *
 * @param grafoOriginal Grafo com as antenas
 * @param linhas Número de linhas da matriz
 * @param colunas Número de colunas da matriz
 * @param nomeFicheiro Nome base do ficheiro
 * @param tipoFicheiro Extensão do ficheiro: ".txt" ou ".bin"
 * @return 200 em caso de sucesso, 500 em erro
 */
int ExportarMatriz(Grafo* grafoOriginal, int linhas, int colunas, const char* nomeFicheiro, const char* tipoFicheiro) {
    char caminhoCompleto[256];
    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s%s", nomeFicheiro, tipoFicheiro);

    FILE* ficheiro = NULL;
    const char* modo = (strcmp(tipoFicheiro, ".bin") == 0) ? "wb" : "w";
    errno_t erro = fopen_s(&ficheiro, caminhoCompleto, modo);
    if (erro != 0 || ficheiro == NULL) {
        perror("Erro ao abrir o ficheiro para escrita");
        return 500;
    }

    for (int y = 0; y < linhas; y++) {
        for (int x = 0; x < colunas; x++) {
            char simbolo = '.';
            Grafo* grafo = grafoOriginal; // cópia do grafo original

            while (grafo != NULL) {
                Ant* ant = grafo->Antena;
                if (ant != NULL && ant->x == x && ant->y == y) {
                    simbolo = ant->freqAntena;
                    break;
                }
                grafo = grafo->listaGrafo;
            }

            if (strcmp(tipoFicheiro, ".bin") == 0) {
                fwrite(&simbolo, sizeof(char), 1, ficheiro);
            }
            else {
                fprintf(ficheiro, "%c", simbolo);
            }
        }

        if (strcmp(tipoFicheiro, ".txt") == 0) {
            fprintf(ficheiro, "\n");
        }
    }

    fclose(ficheiro);
    return 200;
}
#pragma endregion

#pragma region Libertacao_Memoria
/**
 * @brief Liberta a memória alocada para o grafo e suas antenas.
 *
 * @param grafo Ponteiro para a estrutura do grafo
 * @return 200 sempre
 */
int FreeListaAntenas(Grafo* grafo) {
    Grafo* atual = grafo;
    while (atual != NULL) {
		Ant* antena = atual->Antena;
        Ars* aresta = antena->listaAresta;
        // Liberta todas as arestas desta antena
        while (aresta != NULL) {
            Ars* tempAresta = aresta;
            aresta = aresta->proximaAresta;
            free(tempAresta);
        }
        free(antena);
        Grafo* temp = atual;
        atual = atual->listaGrafo;
        free(temp);
    }
    return 200;
}

#pragma endregion