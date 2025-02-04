#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void exibeMenu() {
    printf("\n==== Menu do Grafo ====\n");
    printf("1. Inserir Vértices\n");
    printf("2. Inserir Arestas\n");
    printf("3. Visualizar Grafo\n");
    printf("4. Remover Vértices\n");
    printf("5. Remover Arestas\n");
    printf("6. Sair\n");
    printf("=======================\n");
    printf("Escolha uma opção: ");
}

int main() {
    Grafo *grafo = criaGrafo();
    int opcao, vertice, vertice2;

    do {
        exibeMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: //inserir vertices
                printf("Digite o valor do vértice a ser inserido: ");
                scanf("%d", &vertice);

                insereVertice(vertice, grafo);
                break;

            case 2: //inserir aresta
                printf("Digite o primeiro vértice: ");
                scanf("%d", &vertice);
                printf("Digite o segundo vértice: ");
                scanf("%d", &vertice2);

                insereAresta(vertice, vertice2, grafo);
                break;

            case 3: //visualizar Grafo
                printf("Grafo atual:\n");
                imprimeGrafo(grafo);
                break;

            case 4: //remover vertices
                printf("Digite o valor do vértice a ser removido: ");
                scanf("%d", &vertice);
                removeVertice(vertice, grafo);
                break;

            case 5: //remover arestas
                printf("Digite o primeiro vértice da aresta: ");
                scanf("%d", &vertice);
                printf("Digite o segundo vértice da aresta: ");
                scanf("%d", &vertice2);

                removeAresta(vertice, vertice2, grafo);
                break;

            case 6:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 6);

    limpaGrafo(grafo);
    return 0;
}
