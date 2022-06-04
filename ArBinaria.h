#include <stdio.h>
#include <stdlib.h>

typedef struct NO{
    int dado;
    int FB;
    struct NO *esq;
    struct NO *dir;
}ArBinaria;

ArBinaria* Cria_Arbinaria();
void libera_ArBinaria(ArBinaria *raiz);

int insere_ArBinaria(ArBinaria *raiz, int dado);
int remove_ArBinaria(ArBinaria *raiz, int dado);

int insere_Rec(ArBinaria *raiz, int dado);
int consulta_rec(ArBinaria *raiz, int dado);
int remover_rec(ArBinaria *raiz, int dado);

int vazia_ArBinaria(ArBinaria *raiz);
int altura_ArBinaria(ArBinaria *raiz);
int totalNO_ArBinaria(ArBinaria *raiz);
int consulta_ArBinaria(ArBinaria *raiz, int dado);

void preOrdem(ArBinaria *raiz);
void emOrdem(ArBinaria *raiz);
void posOrdem(ArBinaria *raiz);


// Arvore AVL
int CalculaFB(ArBinaria *raiz);
int SetaFB(ArBinaria *raiz);
ArBinaria* BalanceiaAVL(ArBinaria *raiz);
