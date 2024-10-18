#ifndef PILHA_H
#define PILHA_H

typedef struct no No;
typedef struct Pilha;

void inicializar_pilha(Pilha *);
int pilha_vazia(Pilha *);
void empilhar(Pilha *, float, int *);
void desempilhar(Pilha *, int *);
void imprimir_pilha(Pilha *, int *);
void imprimir_topo(Pilha *, int *);
void excluir_pilha(Pilha *, int *);

#endif