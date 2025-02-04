typedef struct tipo_elemento {
    int valor;
    int linha;
    struct tipo_elemento *proximo;
} tipo_elemento;

typedef struct tipo_linha {
    int ID_Coluna;
    struct tipo_linha *proximo;
    tipo_elemento *inicio;
} tipo_linha;

typedef struct {
    int qtd_linhas;
    int qtd_colunas;
    tipo_linha *inicio;
} Tipo_Mat_Esparsa;

Tipo_Mat_Esparsa* criar_matriz(int linhas, int colunas);
tipo_linha* criar_coluna(int coluna);
tipo_elemento* criar_elemento(int valor, int linha);
void inserir_elemento(Tipo_Mat_Esparsa *matriz, int linha, int coluna, int valor);
int obter_elemento(Tipo_Mat_Esparsa *matriz, int linha, int coluna);
void exibir_matriz(Tipo_Mat_Esparsa *matriz);
void apaga_matriz(Tipo_Mat_Esparsa *matriz);
void cria_transposta(Tipo_Mat_Esparsa *A, Tipo_Mat_Esparsa **B);
Tipo_Mat_Esparsa *somar_matrizes(Tipo_Mat_Esparsa *mat1, Tipo_Mat_Esparsa *mat2);
Tipo_Mat_Esparsa* multiplicar_matrizes(Tipo_Mat_Esparsa *matriz1, Tipo_Mat_Esparsa *matriz2);
