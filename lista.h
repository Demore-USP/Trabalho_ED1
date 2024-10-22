#ifndef LISTA_H
#define LISTA_H

#include "pilha.h"
#include "fila.h"

// Criando a struct que armazena os produtos (por nome)
typedef struct no1
{
    char *produto;
    Fila *usuarios_lances;
    Pilha *lances;
    struct no1 *prox;
} No1;

// Ponteiros de início e fim da lista de produtos
typedef struct Lista
{
    No1 *ini;
    No1 *fim;
} Lista;

void inicializar_lista(Lista *);
int lista_vazia(Lista *);
void inserir_na_lista(Lista *, char *, int *);
void remover_da_lista(Lista *, char *, int *);
int esta_na_lista(Lista *, char *, int *);
No1 *acha_produto(Lista *, char *, int *);
void imprimir_lista(Lista *, int *);
void excluir_lista(Lista *, int *);

#endif
