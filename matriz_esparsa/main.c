#include <stdio.h>
#include "matriz_esparsa.c"

int main() 
{
    Tipo_Mat_Esparsa *matriz = criar_matriz(6, 7);
    inserir_elemento(matriz, 0, 0, 2);
    inserir_elemento(matriz, 1, 5, 45); 
    inserir_elemento(matriz, 1, 6, 13);
    inserir_elemento(matriz, 2, 4, 89);
    inserir_elemento(matriz, 3, 2, 12);
    inserir_elemento(matriz, 5, 4, 3);

    Tipo_Mat_Esparsa *matriz2 = criar_matriz(6, 7);
    inserir_elemento(matriz2, 0, 0, 1);
    inserir_elemento(matriz2, 1, 3, 40); 
    inserir_elemento(matriz2, 1, 1, 10);
    inserir_elemento(matriz2, 2, 4, 1);
    inserir_elemento(matriz2, 3, 2, 10);
    inserir_elemento(matriz2, 5, 4, 3);

    Tipo_Mat_Esparsa *matriz3 = criar_matriz(7, 3);
    inserir_elemento(matriz3, 0, 0, 1);
    inserir_elemento(matriz3, 1, 1, 2); 
    inserir_elemento(matriz3, 2, 2, 3);
    inserir_elemento(matriz3, 3, 0, 4);
    inserir_elemento(matriz3, 4, 1, 5);
    inserir_elemento(matriz3, 5, 2, 6);
    inserir_elemento(matriz3, 6, 0, 7);


    printf("Buscando elementos na matriz: \n");
    printf("Exibindo a matriz:\n");
    exibir_matriz(matriz);
    int valor = obter_elemento(matriz, 2, 4);
    printf("Valor na linha 2, coluna 4: %d\n", valor);
    printf("------------------------------------------------------------\n");

    //transposta
    printf("\nCriando a transposta: \n");
    printf("Matriz original:\n");
    exibir_matriz(matriz);

    Tipo_Mat_Esparsa *transposta = NULL;
    cria_transposta(matriz, &transposta);

    printf("\nMatriz transposta:\n");
    exibir_matriz(transposta);
    printf("------------------------------------------------------------\n");

    //somando matrizes
    printf("\nSomando duas matrizes: \n");

    printf("Matriz 1:\n");
    exibir_matriz(matriz);
    printf("\nMatriz 2:\n");
    exibir_matriz(matriz2);
    Tipo_Mat_Esparsa *resultado = somar_matrizes(matriz, matriz2);
    printf("\nMatriz resultante da soma:\n");
    exibir_matriz(resultado);
    printf("------------------------------------------------------------\n");

    Tipo_Mat_Esparsa *matriz_mult = multiplicar_matrizes(matriz, matriz3);
    printf("Multiplicação entre duas matrizes: \n");
    printf("Matriz 1:\n");
    exibir_matriz(matriz);
    printf("\nMatriz 3:\n");
    exibir_matriz(matriz3);
    printf("\nResultado da multiplicação das matrizes 1 e 3:\n");
    exibir_matriz(matriz_mult);

    apaga_matriz(matriz);
    apaga_matriz(matriz2);
    apaga_matriz(matriz3);
    apaga_matriz(transposta);
    apaga_matriz(resultado);
    apaga_matriz(matriz_mult);
    return 0;
}