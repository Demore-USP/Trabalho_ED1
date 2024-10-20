#ifndef LISTA_H
#define LISTA_H

typedef struct no No;
typedef struct Lista;

void inicializar_lista(Lista *);
int lista_vazia(Lista *); 
void inserir_na_lista(Lista *, char *, int *);
void remover_da_lista(Lista *, char *, int *);
void imprimir_lista(Lista *, int *);
void excluir_lista(Lista *, int *);

#endif 
