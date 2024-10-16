//==========================================================================================================
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//pilha:
typedef struct lance {
    float valor;
    struct lance *prox;
} Lance;

typedef struct {
    Lance *topo;
} Pilha;

void inicializar_pilha(Pilha *p) {
    p->topo = NULL;
}

void empilhar(Pilha *p, float valor, int *erro) {
    Lance *novo = (Lance *)malloc(sizeof(Lance));
    if (novo == NULL) {
        *erro = 1;
        return;
    }
    novo->valor = valor;
    novo->prox = p->topo;
    p->topo = novo;
    *erro = 0;
}

void desempilhar(Pilha *p, int *erro) {
    if (p->topo == NULL) {
        *erro = 1;
        return;
    }
    Lance *temp = p->topo;
    p->topo = p->topo->prox;
    free(temp);
    *erro = 0;
}

int pilha_vazia(Pilha *p) {
    return (p->topo == NULL);
}  