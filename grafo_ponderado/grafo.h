#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>

//aresta com peso
typedef struct Aresta {
    int verticeDestino;
    int peso;
    struct Aresta* prox;
} Aresta;


typedef struct Vertice {
    int id;
    Aresta* adjacente;
    struct Vertice* prox;
} Vertice;


typedef struct Grafo {
    Vertice* vertices;
    int numVertices;
} Grafo;


Grafo* criaGrafo();
Vertice* criaVertice(int vertice);
Aresta* criaAresta(int verticeDestino, int peso);
Vertice* encontraVertice(int v, Grafo *g);
int arestaExiste(Vertice *v, int aresta);
void liberarGrafo(Grafo* grafo);
void inserirVertice(Grafo* grafo, int id);
void inserirAresta(Grafo* grafo, int origem, int destino, int peso);
void removerAresta(Grafo* grafo, int origem, int destino);
void removerVertice(Grafo* grafo, int id);
void visualizarGrafo(Grafo* grafo);
int grauVertice(Grafo* grafo, int id);
bool verificarConexo(Grafo* grafo);
void converterParaMatriz(Grafo* grafo);

#endif
