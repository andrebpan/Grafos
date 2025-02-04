#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

Aresta *criaAresta(int aresta) {
    Aresta *novo = (Aresta *)malloc(sizeof(Aresta));
    novo->aresta = aresta;
    novo->next = NULL;
    return novo;
}

Vertice *criaVertice(int vertice) {
    Vertice *novo = (Vertice *)malloc(sizeof(Vertice));
    novo->vertice = vertice;
    novo->head = NULL;
    novo->next = NULL;
    return novo;
}

Grafo *criaGrafo() {
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    g->head = NULL;
    return g;
}

Vertice *encontraVertice(int vertice, Grafo *g) {
    Vertice *aux = g->head;
    while (aux != NULL) {
        if (aux->vertice == vertice) return aux;
        aux = aux->next;
    }
    return NULL;
}

int arestaExiste(Vertice *v, int aresta) {
    Aresta *aux = v->head;
    while (aux != NULL) {
        if (aux->aresta == aresta) return 1;
        aux = aux->next;
    }
    return 0;
}

void insereVertice(int vertice, Grafo *g) {
    if (encontraVertice(vertice, g) != NULL) {
        printf("Erro: O vértice %d já existe no grafo.\n", vertice);
        return; //retorna sem adicionar o vertice duplicado
    }

    Vertice *novo = criaVertice(vertice);
    if (g->head == NULL || g->head->vertice > vertice) {//adicionar no inicio
        novo->next = g->head;
        g->head = novo;
    } else {
        Vertice *aux = g->head;
        while (aux->next != NULL && aux->next->vertice < vertice) {//adicionar no meio
            aux = aux->next;
        }
        novo->next = aux->next;
        aux->next = novo;
    }
    printf("Vértice %d inserido com sucesso!\n", vertice);
}

void insereAresta(int vertice1, int vertice2, Grafo *g) {
    //verifica se os vértices existem no grafo
    Vertice *v1 = encontraVertice(vertice1, g);
    Vertice *v2 = encontraVertice(vertice2, g);

    if (v1 == NULL || v2 == NULL) {
        printf("Erro: Um ou ambos os vértices (%d, %d) não existem no grafo!\n", vertice1, vertice2);
        return;
    }

    //verifica se a aresta já existe em v1
    if (arestaExiste(v1, vertice2)) {
        printf("Erro: A aresta entre %d e %d já existe!\n", vertice1, vertice2);
        return;
    }

    //cria a aresta e adiciona nas listas dos dois vertices
    //inserir aresta de v1 para v2
    Aresta *novaAresta1 = criaAresta(vertice2);
    novaAresta1->next = v1->head;
    v1->head = novaAresta1;

    //inserir aresta de v2 para v1
    Aresta *novaAresta2 = criaAresta(vertice1);
    novaAresta2->next = v2->head;
    v2->head = novaAresta2;

    printf("Aresta entre %d e %d inserida com sucesso!\n", vertice1, vertice2);
}


void removeAresta(int vertice1, int vertice2, Grafo *g) {
    //encontrar os vertices no grafo
    Vertice *v1 = encontraVertice(vertice1, g);
    Vertice *v2 = encontraVertice(vertice2, g);

    if (v1 == NULL || v2 == NULL) {
        printf("Erro: Um ou ambos os vértices não existem no grafo!\n");
        return;
    }

    //remover a aresta de v1 para v2
    Aresta *aux = v1->head, *anterior = NULL;
    while (aux != NULL && aux->aresta != vertice2) {//até encontrar o vertice
        anterior = aux;
        aux = aux->next;
    }
    if (aux != NULL) {
        if (anterior == NULL) {//primeira da lista
            v1->head = aux->next;
        } else {//anterior->next, ignora a aresta a ser removida
            anterior->next = aux->next;
        }
        free(aux);//libera a memoria da aresta removida
    }

    //remover a aresta de v2 para v1
    aux = v2->head, anterior = NULL;
    while (aux != NULL && aux->aresta != vertice1) {
        anterior = aux;
        aux = aux->next;
    }
    if (aux != NULL) {
        if (anterior == NULL) {
            v2->head = aux->next;
        } else {
            anterior->next = aux->next;
        }
        free(aux);
    }

    printf("Aresta entre %d e %d removida com sucesso!\n", vertice1, vertice2);
}


void removeTodasArestas(Vertice *v) {
    Aresta *aux;
    while (v->head != NULL) {
        aux = v->head;
        v->head = v->head->next;
        free(aux);
    }
}

void removeVertice(int vertice, Grafo *g) {
    //encontrar o vertice e seu anterior na lista de vertices
    Vertice *aux = g->head, *anterior = NULL;

    while (aux != NULL && aux->vertice != vertice) {
        anterior = aux;
        aux = aux->next;
    }

    if (aux != NULL) {
        //remover todas as arestas do vertice
        while (aux->head != NULL) {
            int conectado = aux->head->aresta; //vertice conectado
            removeAresta(vertice, conectado, g); //remove a aresta
        }

        //remover o vertice da lista de vertices
        if (anterior == NULL) {//inicio da lista
            g->head = aux->next;
        } else {
            anterior->next = aux->next;
        }

        free(aux);
        printf("Vértice %d removido com sucesso!\n", vertice);
    } else {
        printf("Erro: Vértice %d não encontrado no grafo!\n", vertice);
    }
}


void limpaGrafo(Grafo *g) {
    if (g == NULL) return;

    Vertice *aux;
    while (g->head != NULL) {
        aux = g->head;
        g->head = g->head->next;
        removeTodasArestas(aux);
        free(aux);
    }
    free(g);
}

void imprimeGrafo(Grafo *g) {
    Vertice *v = g->head;
    while (v != NULL) {
        printf("Vértice %d: ", v->vertice);
        Aresta *a = v->head;
        while (a != NULL) {
            printf("%d -> ", a->aresta);
            a = a->next;
        }
        printf("NULL\n");
        v = v->next;
    }
}
