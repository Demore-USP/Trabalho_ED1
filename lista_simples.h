#ifndef LISTA_SIMPLES_H
#define LISTA_SIMPLES_H

// Criando a struct que armazena os produtos (por nome)
typedef struct no
{
    char *nome;
    struct no *prox;
} No;

// Ponteiros de início e fim da Lista_simples de produtos
typedef struct Lista_simples
{
    No *ini;
    No *fim;
} Lista_simples;

void inicializar_lista_simples(Lista_simples *);
int lista_simples_vazia(Lista_simples *);
void inserir_lista_simples(Lista_simples *, char *, int *);
void excluir_lista_simples(Lista_simples *, int *);

#endif