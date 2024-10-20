#ifndef FILA_H
#define FILA_H

// Criando a struct que armazena o nome do usuário
typedef struct no3
{
    char *usuario;
    struct no3 *prox;
} No3;

// Ponteiros de início e fim da fila de usuários
typedef struct Fila
{
    No3 *ini;
    No3 *fim;
} Fila;

void inicializar_fila(Fila *);
int fila_vazia(Fila *);
void inserir_na_fila(Fila *, char *, int *);
void remover_da_fila(Fila *, int *);
void imprimir_fila(Fila *, int *);
void imprimir_primeiro_fila(Fila *, int *);
void excluir_fila(Fila *, int *);

#endif