#ifndef GRAFO_H
#define GRAFO_H

typedef struct Aresta {
    int aresta;
    struct Aresta *next;
} Aresta;

typedef struct Vertice {
    int vertice;
    struct Vertice *next;
    Aresta *head;
} Vertice;

typedef struct Grafo {
    Vertice *head;
} Grafo;

//funções de criação
Grafo* criaGrafo();
Vertice* criaVertice(int vertice);
Aresta* criaAresta(int aresta);

Vertice* encontraVertice(int v, Grafo *g);
int arestaExiste(Vertice *v, int aresta);

//funções de inserção
void insereVertice(int vertice, Grafo *g);
void insereAresta(int aresta, int vertice, Grafo *g);

//funções de remoção
void removeAresta(int vertice1, int vertice2, Grafo *g);
void removeTodasArestas(Vertice *v);
void removeVertice(int vertice, Grafo *g);

void imprimeGrafo(Grafo *g);
void limpaGrafo(Grafo *g);

#endif // GRAFO_H
