//==========================================================================================================
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//lista:
typedef struct no {
    char *nome;
    struct no *prox;
} No;

typedef struct {
    No *ini;
    No *fim;
} Lista;

void inicializar_lista(Lista *l) {
    l->ini = NULL;
    l->fim = NULL;
}

void inserir_lista_ordem_alfabetica(Lista *l, char *nome, int *erro) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        *erro = 1;
        return;
    }
    novo->nome = (char *)malloc((strlen(nome) + 1) * sizeof(char));
    if (novo->nome == NULL) {
        free(novo);
        *erro = 1;
        return;
    }
    strcpy(novo->nome, nome);
    novo->prox = NULL;
    No *ant = NULL;
    No *p = l->ini;
    while (p != NULL && strcmp(p->nome, nome) < 0) {
        ant = p;
        p = p->prox;
    }
    if (ant == NULL) {
        novo->prox = l->ini;
        l->ini = novo;
    } else {
        ant->prox = novo;
        novo->prox = p;
    }
    if (p == NULL) {
        l->fim = novo;
    }
    *erro = 0;
}

void remover_lista(Lista *l, char *nome, int *erro) {
    No *ant = NULL;
    No *p = l->ini;
    while (p != NULL && strcmp(p->nome, nome) != 0) {
        ant = p;
        p = p->prox;
    }
    if (p == NULL) {
        *erro = 1;
        return;
    }
    if (ant == NULL) {
        l->ini = p->prox;
    } else {
        ant->prox = p->prox;
    }
    if (p == l->fim) {
        l->fim = ant;
    }
    free(p->nome);
    free(p);
    *erro = 0;
}