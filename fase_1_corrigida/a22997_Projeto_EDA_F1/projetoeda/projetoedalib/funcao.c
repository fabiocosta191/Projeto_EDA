/**
 * @file funcao.c
 * @brief Implementa��o de fun��es para manipula��o de antenas e nefastos.
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
   * @brief L� um ficheiro e cria uma lista de antenas
   *
   * Esta fun��o l� um ficheiro (texto ou bin�rio) e cria uma lista ligada de antenas
   * com base nos caracteres encontrados que n�o sejam pontos ('.').
   *
   * @param nomeFicheiro Nome base do ficheiro (sem extens�o)
   * @param tipoFicheiro Extens�o do ficheiro (".txt" ou outro para bin�rio)
   * @param linhas Ponteiro para armazenar o n�mero de linhas lidas
   * @param colunas Ponteiro para armazenar o n�mero m�ximo de colunas encontradas
   * @return Ant* Retorna a lista de antenas criada ou NULL em caso de erro
   */
Ant* LerLista(const char* nomeFicheiro, const char* tipoFicheiro, int* linhas, int* colunas) {
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
                lista = InserirAntena(lista, linha[x], x, y, id);
                id++; // Incrementa o ID da antena
            }
        }
        y++;
    }

    *linhas = y;
    *colunas = maxColunas;
    Nef* listaNef = EncontrarNefastos(lista, y, maxColunas);

    AntNef* listaAntNef = (AntNef*)malloc(sizeof(AntNef));
    if (listaAntNef == NULL) {
        perror("Erro ao alocar mem�ria para AntNef");
        FreeLista(lista);
        FreeListaNef(listaNef);
        return 1;
    }
    listaAntNef->lista = lista;
    listaAntNef->listaNef = listaNef;

    fclose(ficheiro);
    return listaAntNef;
}

/**
 * @brief Insere uma nova antena na lista
 *
 * Aloca mem�ria para uma nova antena e insere-a no in�cio da lista.
 *
 * @param lista Lista de antenas existente
 * @param freq Car�cter que representa a frequ�ncia da antena
 * @param x Coordenada x da antena
 * @param y Coordenada y da antena
 * @param id Identificador �nico da antena
 * @return Ant* Retorna a lista atualizada com a nova antena
 */
Ant* InserirAntena(Ant* lista, char freq, int x, int y, int id) {
    Ant* novaAntena = (Ant*)malloc(sizeof(Ant));
    if (novaAntena == NULL) {
        perror("Error allocating memory");
        return;
    }
    novaAntena->freqAntena = freq;
    novaAntena->x = x;
    novaAntena->y = y;
    novaAntena->id = id; // Atribui o ID � nova antena
    novaAntena->proxAntena = lista;
    lista = novaAntena;
    return lista;
}

/**
 * @brief Apresenta no ecr� a lista de antenas
 *
 * Percorre a lista de antenas e imprime no ecr� a frequ�ncia, coordenadas e ID de cada uma.
 *
 * @param lista Lista de antenas a apresentar
 * @return int Retorna 1 em caso de sucesso
 */
int ApresentarLista(Ant* lista) {
    Ant* atual = lista;
    while (atual != NULL) {
        printf("Antena: %c, Coordenadas: (%d, %d) | Numero:%d\n", atual->freqAntena, atual->x, atual->y, atual->id);
        atual = atual->proxAntena;
    }
    return 1;
}

/**
 * @brief Apresenta uma matriz representando as antenas e espa�os vazios
 *
 * Gera uma representa��o matricial onde as antenas s�o mostradas com sua frequ�ncia
 * e os espa�os vazios s�o representados por pontos.
 *
 * @param lista Lista de antenas
 * @param linhas N�mero de linhas da matriz
 * @param colunas N�mero de colunas da matriz
 * @return int Retorna 1 em caso de sucesso
 */
int ApresentarMatrizLista(Ant* lista, int linhas, int colunas) {

    for (int y = 0; y < linhas; y++) {
        for (int x = 0; x < colunas; x++) {
            int encontrou = 0;
            Ant* atual = lista;

            while (atual != NULL) {
                if (atual->x == x && atual->y == y) {
                    printf("%c ", atual->freqAntena);
                    encontrou = 1;
                    break;
                }
                atual = atual->proxAntena;
            }
            if (encontrou == 0) printf(". ");
        }
        printf("\n");
    }
    return 1;
}

/**
 * @brief Encontra posi��es nefastas entre antenas
 *
 * Identifica posi��es onde podem ocorrer interfer�ncias entre antenas da mesma frequ�ncia
 * seguindo padr�es geom�tricos espec�ficos.
 *
 * @param lista Lista de antenas a analisar
 * @param linhas N�mero de linhas da �rea de cobertura
 * @param colunas N�mero de colunas da �rea de cobertura
 * @return Nef* Retorna uma lista de posi��es nefastas encontradas
 */
Nef* EncontrarNefastos(Ant* lista, int linhas, int colunas) {
    int menorx, menory, maiorx, maiory, difx, dify, idant1, idant2;
    Nef* listaNef = NULL;
    Ant* listaAnt1 = lista;


    while (listaAnt1 != NULL) {
        Ant* listaAnt2 = lista;

        while (listaAnt2 != NULL) {

            if (listaAnt1->freqAntena == listaAnt2->freqAntena && (listaAnt1->y != listaAnt2->y || listaAnt1->x != listaAnt2->x)) {

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
                    if (menorx >= 0 && menory >= 0 && menorx<=linhas && menory<=colunas)
                    {
                        listaNef = InserirNefasto(listaNef, menorx, menory, idant1, idant2, lista);
                    }
                    if (maiorx <= colunas && maiory <= linhas && maiorx <= linhas && maiory <= colunas)
                    {
                        listaNef = InserirNefasto(listaNef, maiorx, maiory, idant1, idant2, lista);
                    }
                }
                else if (listaAnt1->x > listaAnt2->x && listaAnt1->y < listaAnt2->y || listaAnt1->x < listaAnt2->x && listaAnt1->y > listaAnt2->y)
                {
                    if (maiorx >= 0 && menory >= 0 && maiorx <= linhas && menory <= colunas)
                    {
                        listaNef = InserirNefasto(listaNef, maiorx, menory, idant1, idant2, lista);
                    }
                    if (menorx <= colunas && maiory <= linhas && menorx <= linhas && maiory <= colunas)
                    {
                        listaNef = InserirNefasto(listaNef, menorx, maiory, idant1, idant2, lista);
                    }
                }
            }
            listaAnt2 = listaAnt2->proxAntena;
        }
        listaAnt1 = listaAnt1->proxAntena;
    }
    return listaNef;
}

/**
 * @brief Insere uma nova posi��o nefasta na lista
 *
 * Verifica se a posi��o j� existe na lista antes de inserir uma nova posi��o nefasta.
 *
 * @param listaNef Lista de posi��es nefastas existente
 * @param x Coordenada x da posi��o nefasta
 * @param y Coordenada y da posi��o nefasta
 * @param ant1 ID da primeira antena relacionada
 * @param ant2 ID da segunda antena relacionada
 * @param lista Lista de antenas para valida��o
 * @return Nef* Retorna a lista atualizada de posi��es nefastas
 */
Nef* InserirNefasto(Nef* listaNef, int x, int y, int ant1, int ant2, Ant* lista) {
    Ant* atual = lista;
    while (atual != NULL) {
        if (atual->x == x && atual->y == y) {
            return listaNef;
        }
        atual = atual->proxAntena;
    }

    Nef* temp = listaNef;
    while (temp != NULL)
    {
        if (temp->x == x && temp->y == y && temp->antena1 == ant2 && temp->antena2 == ant1)
        {
            return listaNef;
        }
        temp = temp->proxNef;
    }
    Nef* novoNefasto = (Nef*)malloc(sizeof(Nef));
    if (novoNefasto == NULL) {
        perror("Error allocating memory");
        return;
    }
    novoNefasto->x = x;
    novoNefasto->y = y;
    novoNefasto->antena1 = ant1;
    novoNefasto->antena2 = ant2;
    novoNefasto->proxNef = listaNef;
    listaNef = novoNefasto;
    return listaNef;
}

/**
 * @brief Apresenta no ecr� a lista de posi��es nefastas
 *
 * @param listaNef Lista de posi��es nefastas a apresentar
 * @return int Retorna 1 em caso de sucesso
 */
int ApresentarListaNef(Nef* listaNef) {
    Nef* atual = listaNef;
    while (atual != NULL) {
        printf("Nefasto: (%d, %d) - Antenas: %d e %d\n", atual->x, atual->y, atual->antena1, atual->antena2);
        atual = atual->proxNef;
    }
    return 1;
}

/**
 * @brief Apresenta matriz com antenas e posi��es nefastas
 *
 * Gera uma representa��o matricial mostrando antenas com sua frequ�ncia,
 * posi��es nefastas com '#' e espa�os vazios com '.'.
 *
 * @param lista Lista de antenas
 * @param linhas N�mero de linhas da matriz
 * @param colunas N�mero de colunas da matriz
 * @param listaNef Lista de posi��es nefastas
 * @return int Retorna 1 em caso de sucesso
 */
int ApresentarMatrizListaNef(Ant* lista, int linhas, int colunas, Nef* listaNef) {

    for (int y = 0; y < linhas; y++) {
        for (int x = 0; x < colunas; x++) {
            int encontrou = 0;
            Ant* atual = lista;

            while (atual != NULL) {
                if (atual->x == x && atual->y == y) {
                    printf("%c ", atual->freqAntena);
                    encontrou = 1;
                    break;
                }
                atual = atual->proxAntena;
            }
            if (encontrou == 0) {
                Nef* atualNef = listaNef;
                while (atualNef != NULL) {
                    if (atualNef->x == x && atualNef->y == y) {
                        printf("# ");
                        encontrou = 1;
                        break;
                    }
                    atualNef = atualNef->proxNef;
                }
            }
            if (encontrou == 0) printf(". ");
        }
        printf("\n");
    }
    return 1;
}

/**
 * @brief Remove uma antena da lista e suas posi��es nefastas relacionadas
 *
 * @param listaAntNef Estrutura contendo listas de antenas e posi��es nefastas
 * @param x Coordenada x da antena a remover
 * @param y Coordenada y da antena a remover
 * @return AntNef* Retorna a estrutura atualizada
 */
AntNef* RemoverAntena(AntNef* listaAntNef, int x, int y) {
    Ant* atual = listaAntNef->lista;
    Ant* anterior = NULL;
    int id = 0;


    while (atual != NULL) {
        if (atual->x == x && atual->y == y) {
            if (anterior == NULL) {
                id = atual->id;
                listaAntNef->lista = atual->proxAntena;
            }
            else {
                id = atual->id;
                anterior->proxAntena = atual->proxAntena;
            }
            Nef* atualNef = listaAntNef->listaNef;
            Nef* anteriorNef = NULL;
            while (atualNef != NULL) {
                if (atualNef->antena1 == id || atualNef->antena2 == id) {
                    if (anteriorNef == NULL) {
                        listaAntNef->listaNef = atualNef->proxNef;
                    }
                    else {
                        anteriorNef->proxNef = atualNef->proxNef;
                    }
                }
                anteriorNef = atualNef;
                atualNef = atualNef->proxNef;
            }
            free(atualNef);
            free(atual);
            return listaAntNef;
        }
        anterior = atual;
        atual = atual->proxAntena;
    }
}

/**
 * @brief Adiciona ou atualiza uma antena e recalcula posi��es nefastas
 *
 * Se j� existir uma antena nas coordenadas especificadas, atualiza sua frequ�ncia.
 * Caso contr�rio, insere uma nova antena.
 *
 * @param listaAntNef Estrutura contendo listas de antenas e posi��es nefastas
 * @param freq Frequ�ncia da antena
 * @param x Coordenada x da antena
 * @param y Coordenada y da antena
 * @param linhas N�mero de linhas da �rea de cobertura
 * @param colunas N�mero de colunas da �rea de cobertura
 * @return AntNef* Retorna a estrutura atualizada
 */
AntNef* AdicionarAntena(AntNef* listaAntNef, char freq, int x, int y, int linhas, int colunas) {
    Ant* atual = listaAntNef->lista;
    int id = atual->id + 1;
    int result;
    while (atual != NULL) {
        if (atual->x == x && atual->y == y) {
            atual->freqAntena = freq;
            result = FreeListaNef(listaAntNef->listaNef);
            listaAntNef->listaNef = EncontrarNefastos(listaAntNef->lista, linhas, colunas);
            return listaAntNef;
        }
        atual = atual->proxAntena;
    }

    listaAntNef->lista = InserirAntena(listaAntNef->lista, freq, x, y, id);
    result = FreeListaNef(listaAntNef->listaNef);
    listaAntNef->listaNef = EncontrarNefastos(listaAntNef->lista, linhas, colunas);

    return listaAntNef;
}

/**
 * @brief Liberta a mem�ria alocada para a lista de antenas
 *
 * @param lista Lista de antenas a libertar
 * @return int Retorna 1 em caso de sucesso
 */
int FreeLista(Ant* lista) {
    Ant* atual = lista;
    while (atual != NULL) {
        Ant* temp = atual;
        atual = atual->proxAntena;
        free(temp);
    }
    return 1;
}

/**
 * @brief Liberta a mem�ria alocada para a lista de posi��es nefastas
 *
 * @param listaNef Lista de posi��es nefastas a libertar
 * @return int Retorna 1 em caso de sucesso
 */
int FreeListaNef(Nef* listaNef) {
    Nef* atual = listaNef;
    while (atual != NULL) {
        Nef* temp = atual;
        atual = atual->proxNef;
        free(temp);
    }
    return 1;
}

/**
 * @brief Liberta a mem�ria alocada para a estrutura AntNef
 *
 * @param listaAntNef Estrutura AntNef a libertar
 * @return int Retorna 1 em caso de sucesso
 */
int FreeAntNef(AntNef* listaAntNef) {
	FreeLista(listaAntNef->lista);
	FreeListaNef(listaAntNef->listaNef);
	free(listaAntNef);
	return 1;
}