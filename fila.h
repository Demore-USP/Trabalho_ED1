#ifndef FILA_H
#define FILA_H

typedef struct bloco No;
typedef struct Fila Fila;

void inicializar_fila(Fila *);
int fila_vazia(Fila *); 
void inserir_na_fila(Fila *, char *, int *);
void remover_da_fila(Fila *, char *, int *);
void imprimir_fila_todos(Fila *, int *);
void imprimir_fila(Fila *, int *);
void excluir_fila(Fila *, int *);

#endif 