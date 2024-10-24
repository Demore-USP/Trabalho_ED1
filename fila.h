#ifndef FILA_H
#define FILA_H

// Struct que armazena o nome do usuário
// (lista de nomes para cada produto)
typedef struct no_fila {
    char *usuario;
    struct no_fila *prox;
} No_Fila;

// Ponteiros de início e fim da fila de usuários
typedef struct Fila {
    No_Fila *ini;
    No_Fila *fim;
} Fila;

void inicializar_fila(Fila *);
int fila_vazia(Fila *);
void inserir_na_fila(Fila *, char *, int *);
char *remover_da_fila(Fila *, int *);
void copiar_fila(Fila *, Fila *, int *);
Fila inverter_fila(Fila *, int *);
void excluir_fila(Fila *, int *);
int esta_na_fila(Fila *, char *, int *);

#endif