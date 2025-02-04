// Função para criar uma nova matriz esparsa
#include <stdio.h>
#include <stdlib.h>
#include "matriz_esparsa.h"

Tipo_Mat_Esparsa* criar_matriz(int linhas, int colunas) {
    Tipo_Mat_Esparsa *matriz = (Tipo_Mat_Esparsa*)malloc(sizeof(Tipo_Mat_Esparsa));
    matriz->qtd_linhas = linhas;
    matriz->qtd_colunas = colunas;
    matriz->inicio = NULL;
    return matriz;
}

tipo_linha* criar_coluna(int coluna) {
    tipo_linha *nova_coluna = (tipo_linha*)malloc(sizeof(tipo_linha));
    nova_coluna->ID_Coluna = coluna;
    nova_coluna->proximo = NULL;
    nova_coluna->inicio = NULL;
    return nova_coluna;
}

tipo_elemento* criar_elemento(int valor, int linha) {
    tipo_elemento *novo_elemento = (tipo_elemento*)malloc(sizeof(tipo_elemento));
    novo_elemento->valor = valor;
    novo_elemento->linha = linha;
    novo_elemento->proximo = NULL;
    return novo_elemento;
}

void inserir_elemento(Tipo_Mat_Esparsa *matriz, int linha, int coluna, int valor) {
    if (valor == 0) return; //nao armazena zeros
    
    tipo_linha *col = matriz->inicio, *prev_col = NULL;
    while (col != NULL && col->ID_Coluna < coluna) {//percorre até encontrar a posicao correta
        prev_col = col;
        col = col->proximo;
    }
    if (col == NULL || col->ID_Coluna != coluna) {//cria coluna caso não encontre
        tipo_linha *nova_coluna = criar_coluna(coluna);
        if (prev_col == NULL) {//se for nulo, cria a primeira coluna
            nova_coluna->proximo = matriz->inicio;
            matriz->inicio = nova_coluna;//passa a ser o inicio
        } else {
            nova_coluna->proximo = prev_col->proximo;//insere entre duas colunas
            prev_col->proximo = nova_coluna;
        }
        col = nova_coluna;
    }

    //insere o elemento na lista de elementos da coluna
    tipo_elemento *elem = col->inicio, *prev_elem = NULL;
    while (elem != NULL && elem->linha < linha) {//passa até encontrar a linha
        prev_elem = elem;
        elem = elem->proximo;
    }
    if (elem == NULL || elem->linha != linha) {//se não encontrou, cria um novo elemento de linha
        tipo_elemento *novo_elemento = criar_elemento(valor, linha);
        if (prev_elem == NULL) {//se a posicao é no inicio da lista, o novo elemento é inserido no inicio, caso contrario é inserido apos prev_elem
            novo_elemento->proximo = col->inicio;
            col->inicio = novo_elemento;
        } else {
            novo_elemento->proximo = prev_elem->proximo;
            prev_elem->proximo = novo_elemento;
        }
    } else {
        elem->valor = valor;//atualiza o valor se o elemento já existe
    }
}

//função para obter um elemento da matriz
int obter_elemento(Tipo_Mat_Esparsa *matriz, int linha, int coluna) {
    tipo_linha *col = matriz->inicio;//aponta para o inicio
    while (col != NULL && col->ID_Coluna < coluna) {//procura a coluna
        col = col->proximo;
    }
    if (col == NULL || col->ID_Coluna != coluna) {// se nao existe, retorna 0
        return 0;
    }
    tipo_elemento *elem = col->inicio;// se a coluna foi encontrada, inicia a busca nas linhas
    while (elem != NULL && elem->linha < linha) {//percorre ate encontrar
        elem = elem->proximo;
    }
    if (elem == NULL || elem->linha != linha) {
        return 0;
    }
    return elem->valor;
}

void exibir_matriz(Tipo_Mat_Esparsa *matriz) {
    for (tipo_linha *col = matriz->inicio; col != NULL; col = col->proximo) {
        for (tipo_elemento *elem = col->inicio; elem != NULL; elem = elem->proximo) {
            printf("[%d][%d] = %d\n", elem->linha, col->ID_Coluna, elem->valor);
        }
    }
}


void apaga_matriz(Tipo_Mat_Esparsa *matriz) {
    tipo_linha *col = matriz->inicio;
    while (col != NULL) {
        tipo_elemento *elem = col->inicio;
        while (elem != NULL) {
            tipo_elemento *temp_elem = elem;
            elem = elem->proximo;
            free(temp_elem);
        }
        tipo_linha *temp_col = col;
        col = col->proximo;
        free(temp_col);
    }
    free(matriz);
}


void cria_transposta(Tipo_Mat_Esparsa *A, Tipo_Mat_Esparsa **B) {
    *B = criar_matriz(A->qtd_colunas, A->qtd_linhas); //cria a nova matriz com linhas e colunas invertidos

    tipo_linha *coluna_atual = A->inicio; //lista de colunas da matriz original

    while (coluna_atual != NULL) {
        tipo_elemento *elem = coluna_atual->inicio; //lista de elementos(linha) dentro da coluna
        while (elem != NULL) {
            //insere na matriz transposta, trocando linha e coluna
            inserir_elemento(*B, coluna_atual->ID_Coluna, elem->linha, elem->valor);
            elem = elem->proximo;
        }
        coluna_atual = coluna_atual->proximo;//vai para a proxima coluna
    }
}


Tipo_Mat_Esparsa* somar_matrizes(Tipo_Mat_Esparsa *matriz1, Tipo_Mat_Esparsa *matriz2) {
    Tipo_Mat_Esparsa *resultado = criar_matriz(matriz1->qtd_linhas, matriz1->qtd_colunas);

    for (int i = 0; i < matriz1->qtd_linhas; i++) {
        for (int j = 0; j < matriz1->qtd_colunas; j++) {
            int valor1 = obter_elemento(matriz1, i, j);
            int valor2 = obter_elemento(matriz2, i, j);
            int soma = valor1 + valor2;

            inserir_elemento(resultado, i, j, soma);
        }
    }
    return resultado;
}

Tipo_Mat_Esparsa* multiplicar_matrizes(Tipo_Mat_Esparsa *matriz1, Tipo_Mat_Esparsa *matriz2) {
    //verifica as dimensões das matrizes
    if (matriz1->qtd_colunas != matriz2->qtd_linhas) {
        printf("Matrizes com dimensões incompatíveis para multiplicação.\n");
        return NULL;
    }

    Tipo_Mat_Esparsa *resultado = criar_matriz(matriz1->qtd_linhas, matriz2->qtd_colunas);

    //percorre cada linha de matriz1
    for (int i = 0; i < matriz1->qtd_linhas; i++) {
        //percorre cada coluna de matriz2
        for (int j = 0; j < matriz2->qtd_colunas; j++) {
            int soma = 0;

            for (int k = 0; k < matriz1->qtd_colunas; k++) {
                //elementos não nulos de ambas as matrizes
                int valor1 = obter_elemento(matriz1, i, k);//linha e coluna da mat1
                int valor2 = obter_elemento(matriz2, k, j);//linha e coluna da mat2

                soma += valor1 * valor2;                
            }
            inserir_elemento(resultado, i, j, soma);
        }
    }
    return resultado;
}