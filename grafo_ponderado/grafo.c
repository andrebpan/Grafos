#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"

Aresta* criaAresta(int verticeDestino, int peso) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->verticeDestino = verticeDestino;
    novaAresta->peso = peso;
    novaAresta->prox = NULL;  //inicializa o ponteiro para a próxima aresta como NULL
    return novaAresta;
}


Vertice* criaVertice(int id) {
    Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
    novoVertice->id = id;
    novoVertice->adjacente = NULL;  //inicializa a lista de arestas como NULl
    novoVertice->prox = NULL;       //inicializa o ponteiro para o próximo vértice como NULL
    return novoVertice;
}


Grafo* criaGrafo() {
    Grafo* novoGrafo = (Grafo*)malloc(sizeof(Grafo));
    novoGrafo->vertices = NULL;  //inicializa a lista de vértices como NULL
    novoGrafo->numVertices = 0;  //inicializa o número de vértices como 0
    return novoGrafo;
}

Vertice* encontraVertice(int id, Grafo* g) {
    Vertice* aux = g->vertices;
    while (aux != NULL) {
        if (aux->id == id) return aux;  //encontrou
        aux = aux->prox;  //próximo vértice
    }
    return NULL;  //não encontrado
}

int arestaExiste(Vertice* v, int verticeDestino) {
    Aresta* aux = v->adjacente;
    while (aux != NULL) {
        if (aux->verticeDestino == verticeDestino) return 1;  //aresta encontrada
        aux = aux->prox;  //próxima aresta
    }
    return 0;  //aresta não encontrada
}


//inserir um vértice no grafo
void inserirVertice(Grafo* grafo, int id) {
    //verifica se o vértice já existe no grafo
    if (encontraVertice(id, grafo) != NULL) {
        printf("Erro: Vértice com ID %d já existe no grafo.\n", id);
        return; 
    }

    //novo vértice usando a função criaVertice
    Vertice* novoVertice = criaVertice(id);

    // Inserindo o vértice no final da lista de vértices
    if (grafo->vertices == NULL) {
        grafo->vertices = novoVertice;
    } else {
        Vertice* v = grafo->vertices;
        while (v->prox != NULL) {
            v = v->prox;
        }
        v->prox = novoVertice;
    }
    
    grafo->numVertices++;

    printf("Vértice %d inserido com sucesso.\n", id);
}

void inserirAresta(Grafo *grafo, int idOrigem, int idDestino, int peso) {
    //verificar se os vertices de origem e destino existem
    Vertice* verticeOrigem = encontraVertice(idOrigem, grafo);
    Vertice* verticeDestino = encontraVertice(idDestino, grafo);

    if (verticeOrigem == NULL) {
        printf("Erro: Vértice de origem %d não encontrado.\n", idOrigem);
        return; //vertice de origem não encontrado
    }

    if (verticeDestino == NULL) {
        printf("Erro: Vértice de destino %d não encontrado.\n", idDestino);
        return; //vertice de destino não encontrado
    }

    //verificar se a aresta já existe
    if (arestaExiste(verticeOrigem, idDestino)) {
        printf("Erro: Aresta entre %d e %d já existe.\n", idOrigem, idDestino);
        return;
    }

    //nova aresta
    Aresta* novaAresta = criaAresta(idDestino, peso);
    novaAresta->prox = verticeOrigem->adjacente; //adicionar a aresta na lista de adjacência do vértice de origem
    verticeOrigem->adjacente = novaAresta;

    novaAresta = criaAresta(idOrigem, peso);
    novaAresta->prox = verticeDestino->adjacente; //adicionar a aresta na lista de adjacência do vértice de destino
    verticeDestino->adjacente = novaAresta;

    printf("Aresta entre %d e %d com peso %d adicionada com sucesso.\n", idOrigem, idDestino, peso);
}


void removerAresta(Grafo* grafo, int origem, int destino) {
    //encontrar o vértice de origem
    Vertice* vOrigem = encontraVertice(origem, grafo);
    if (vOrigem == NULL) {
        printf("Vértice de origem %d não encontrado.\n", origem);
        return;
    }

    //remover a aresta de origem -> destino
    Aresta* a = vOrigem->adjacente;
    Aresta* prev = NULL;
    while (a != NULL && a->verticeDestino != destino) {//percorre enquanto aresta nao for null e nao tenha encontrado o destino
        prev = a;
        a = a->prox;
    }
    if (a == NULL) {
        printf("Aresta %d -> %d não encontrada.\n", origem, destino);
        return;
    }
    if (prev == NULL) {//primeira da lista
        vOrigem->adjacente = a->prox;
    } else {
        prev->prox = a->prox;//se nao for a primeira da lista, "pula" a aresta, substituindo pelo valor da proxima
    }
    free(a);

    //encontrar o vértice de destino
    Vertice* vDestino = encontraVertice(destino, grafo);
    if (vDestino == NULL) {
        printf("Vértice de destino %d não encontrado.\n", destino);
        return;
    }

    //remover a aresta reversa (destino -> origem)
    a = vDestino->adjacente;
    prev = NULL;
    while (a != NULL && a->verticeDestino != origem) {
        prev = a;
        a = a->prox;
    }
    if (a != NULL) {
        if (prev == NULL) {
            vDestino->adjacente = a->prox;
        } else {
            prev->prox = a->prox;
        }
        free(a);
    }

    printf("Aresta %d -> %d removida com sucesso.\n", origem, destino);
}


void removerVertice(Grafo* grafo, int id) {
    // remove todas as arestas conectadas ao vértice antes de remove-lo
    Vertice* vAtual = grafo->vertices;
    while (vAtual != NULL) {
        removerAresta(grafo, vAtual->id, id);
        vAtual = vAtual->prox;
    }

    //encontrar o vértice a ser removido
    Vertice* v = encontraVertice(id, grafo);
    if (v == NULL) {
        printf("Vértice %d não encontrado.\n", id);
        return;
    }

    //remove todas as arestas do próprio vértice (v->adjacente)
    Aresta* a = v->adjacente;
    while (a != NULL) {
        Aresta* temp = a;
        a = a->prox;
        free(temp);
    }

    //ajustar lista de vértices(removendo o vertice)
    Vertice* prev = NULL;
    Vertice* current = grafo->vertices;
    while (current != NULL && current != v) {
        prev = current;
        current = current->prox;
    }

    if (prev == NULL) {
        grafo->vertices = v->prox;
    } else {
        prev->prox = v->prox;
    }

    free(v);
    grafo->numVertices--;

    printf("Vértice %d removido com sucesso.\n", id);
}

//visualizar o grafo
void visualizarGrafo(Grafo* grafo) {
    Vertice* v = grafo->vertices;
    while (v != NULL) {
        printf("Vértice %d: ", v->id);
        Aresta* a = v->adjacente;
        while (a != NULL) {
            printf("-> %d (Peso: %d) ", a->verticeDestino, a->peso);
            a = a->prox;
        }
        printf("\n");
        v = v->prox;
    }
}

//calcular o grau de um vértice
int grauVertice(Grafo* grafo, int id) {
    Vertice* v = grafo->vertices;
    while (v != NULL && v->id != id) {//verifica se vertice existe
        v = v->prox;
    }
    if (v == NULL) return -1; //vértice não encontrado

    int grau = 0;
    Aresta* a = v->adjacente;
    while (a != NULL) {
        grau++;
        a = a->prox;
    }
    return grau;
}

//busca DFS(busca em profundidade)
void dfs(Grafo* grafo, Vertice* v, bool* visitado) {
    visitado[v->id] = true;  //marcar o vértice como visitado

    Aresta* a = v->adjacente;
    while (a != NULL) {
        //encontrar o vértice de destino e chamar DFS se não foi visitado
        Vertice* adj = grafo->vertices;
        while (adj != NULL && adj->id != a->verticeDestino) {
            adj = adj->prox;//procura o vertice de destino da aresta
        }
        if (adj != NULL && !visitado[adj->id]) {
            dfs(grafo, adj, visitado);  //chamada recursiva, indo para o proximo vertice
        }

        //verificar o caminho reverso
        if (!visitado[a->verticeDestino]) {
            dfs(grafo, adj, visitado);
        }

        a = a->prox;
    }
}


bool verificarConexo(Grafo* grafo) {

    //criar um vetor para marcar os vértices visitados
    bool* visitado = (bool*)calloc(grafo->numVertices, sizeof(bool));

    //iniciar DFS a partir do primeiro vertice
    dfs(grafo, grafo->vertices, visitado);

    //verificar se todos os vertices foram visitados
    bool conexo = true;
    Vertice* v = grafo->vertices;
    while (v != NULL) {
        if (!visitado[v->id]) {
            conexo = false;
            break;
        }
        v = v->prox;
    }

    free(visitado);

    return conexo;
}


// Função para destruir o grafo e liberar memória
void liberarGrafo(Grafo* grafo) {
    Vertice* v = grafo->vertices;
    while (v != NULL) {
        Aresta* a = v->adjacente;
        while (a != NULL) {
            Aresta* tempAresta = a;
            a = a->prox;
            free(tempAresta);
        }
        Vertice* tempVertice = v;
        v = v->prox;
        free(tempVertice);
    }
    free(grafo);
}


void converterParaMatriz(Grafo *grafo) {

    //criando a matriz de adjacência com base no número de vértices
    int** matriz = (int**)malloc(grafo->numVertices * sizeof(int*));
    for (int i = 0; i < grafo->numVertices; i++) {
        matriz[i] = (int*)malloc(grafo->numVertices * sizeof(int));
        for (int j = 0; j < grafo->numVertices; j++) {
            matriz[i][j] = 0; //inicializa com 0 (sem arestas)
        }
    }

    //criando o mapeamento de IDs para índices
    int* idParaIndice = (int*)malloc(grafo->numVertices * sizeof(int));
    Vertice* v = grafo->vertices;
    int i = 0;
    while (v != NULL) {
        idParaIndice[i] = v->id;
        v = v->prox;
        i++;
    }

    //preencher a matriz com os pesos
    v = grafo->vertices;
    for (i = 0; v != NULL; i++, v = v->prox) {//percorre vertices
        Aresta* a = v->adjacente;
        while (a != NULL) {//percorre arestas
            //encontrarVertice para localizar o índice do vértice destino
            Vertice* destino = encontraVertice(a->verticeDestino, grafo);
            if (destino != NULL) {
                int indiceDestino = -1;
                for (int k = 0; k < grafo->numVertices; k++) {
                    if (idParaIndice[k] == destino->id) {//encontrou o id do destino
                        indiceDestino = k;//armazena o indice correspondente
                        break;
                    }
                }

                if (indiceDestino != -1) {//se encontrou o vertice destino, preenche a matriz com o peso
                    matriz[i][indiceDestino] = a->peso;
                    matriz[indiceDestino][i] = a->peso;  
                }
            }
            a = a->prox;
        }
    }

    
    printf("Matriz de Adjacência:\n");
    for (i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numVertices; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < grafo->numVertices; i++) {
        free(matriz[i]);
    }
    free(matriz);
    free(idParaIndice);
}


