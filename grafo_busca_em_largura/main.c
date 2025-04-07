#include <stdio.h>
#include "grafo.h"

int main() {
    Grafo* grafo = criaGrafo();
    int escolha, id1, id2, peso;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir Vértice\n");
        printf("2. Inserir Aresta\n");
        printf("3. Remover Vértice\n");
        printf("4. Remover Aresta\n");
        printf("5. Visualizar Grafo\n");
        printf("6. Informar grau de um vértice\n");
        printf("7. Informar se o grafo é conexo\n");
        printf("8. Converter grafo para Matriz de Adjacência\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o ID do vértice: ");
                scanf("%d", &id1);
                inserirVertice(grafo, id1);
                break;
            case 2:
                printf("Digite o ID do vértice de origem: ");
                scanf("%d", &id1);
                printf("Digite o ID do vértice de destino: ");
                scanf("%d", &id2);
                printf("Digite o peso da aresta: ");
                scanf("%d", &peso);
                inserirAresta(grafo, id1, id2, peso);
                break;
            case 3:
                printf("Digite o ID do vértice a ser removido: ");
                scanf("%d", &id1);
                removerVertice(grafo, id1);
                break;
            case 4:
                printf("Digite o ID do vértice de origem: ");
                scanf("%d", &id1);
                printf("Digite o ID do vértice de destino: ");
                scanf("%d", &id2);
                removerAresta(grafo, id1, id2);
                break;
            case 5:
                visualizarGrafo(grafo);
                break;
            case 6:
                printf("Digite o ID do vértice: ");
                scanf("%d", &id1);
                printf("Grau do vértice %d: %d\n", id1, grauVertice(grafo, id1));
                break;
            case 7:
                if (verificarConexo(grafo)) {
                    printf("O grafo é conexo.\n");
                } else {
                    printf("O grafo não é conexo.\n");
                }
                break;
            case 8:
                converterParaMatriz(grafo);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (escolha != 0);

    liberarGrafo(grafo);
    return 0;
}
