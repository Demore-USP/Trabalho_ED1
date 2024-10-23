#ifndef LISTA_SIMPLES_H
#define LISTA_SIMPLES_H

// Criando a struct que armazena os produtos (por nome)
typedef struct no {
    char *nome;
    struct no *prox;
} No;

// Ponteiros de início e fim da Lista_simples de produtos
typedef struct Lista_simples {
    No *ini;
    No *fim;
} Lista_simples;

void inicializar_Lista_simples(Lista_simples *);
int Lista_simples_vazia(Lista_simples *);
void inserir_na_Lista_simples(Lista_simples *, char *, int *);
void remover_da_Lista_simples(Lista_simples *, char *, int *);


#endif