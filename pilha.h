#ifndef PILHA_H
#define PILHA_H

// Criando a struct que armazena os valores dos lances
typedef struct no_pilha {
    float valor;
    struct no_pilha *prox;
} No_Pilha;

// Ponteiro topo da Pilha (sempre aponta pro lance mais alto)
typedef struct Pilha {
    No_Pilha *topo;
} Pilha;

void inicializar_pilha(Pilha *);
int pilha_vazia(Pilha *);
void empilhar(Pilha *, float, int *);
void desempilhar(Pilha *, int *);
void imprimir_pilha(Pilha *, int *);
void imprimir_topo(Pilha *, int *);
void excluir_pilha(Pilha *, int *);

#endif