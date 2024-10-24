/*
Caso haja algum erro em qualquer função, a função retorna 1.
Desse modo, cabe ao usuário do TAD verificar o motivo do erro,
de acordo a função chamada.
*/

// Includes padrão
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que inicializa a Pilha
void inicializar_pilha(Pilha *P)
{
    P->topo = NULL;
}

// Função que verifica se a pilha está vazia
// (retorna 1 se está vazia ou 0 se não está)
int pilha_vazia(Pilha *P)
{
    return (P->topo == NULL);
}

// Função que insere um lance na pilha
void empilhar(Pilha *P, float valor, int *erro)
{
    No_Pilha *novo = (No_Pilha *)malloc(sizeof(No_Pilha)); // Aloca memória para um novo Nó
    if (novo == NULL)
    {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // O novo lance aponta para o lance anterior (antigo topo), e o topo
    // passa a apontar para o novo lance
    novo->valor = valor;
    novo->prox = P->topo;
    P->topo = novo;
    *erro = 0;
}

// Função que remove o último lance da pilha (simplesmente apaga o nó)
float desempilhar(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 1;
        return 0; // Caso a pilha esteja vazia, retorna e o erro é atualizado
    }
    float valor = P->topo->valor;
    No_Pilha *temp = P->topo;
    P->topo = P->topo->prox;
    free(temp);
    *erro = 0;
    return valor;
}

void copiar_pilha(Pilha *origem, Pilha *destino, int *erro)
{
    if (pilha_vazia(origem))
    {
        *erro = 1;
        return;
    }

    Pilha pilha_aux;
    inicializar_pilha(&pilha_aux); // Inicializa uma pilha auxiliar

    No_Pilha *no_pilha = origem->topo;

    // Desempilha da origem e empilha na pilha auxiliar
    while (no_pilha != NULL)
    {
        empilhar(&pilha_aux, no_pilha->valor, erro);
        if (*erro != 0)
            return;
        no_pilha = no_pilha->prox;
    }

    // Desempilha da auxiliar para a pilha destino (mantém a ordem original)
    while (!pilha_vazia(&pilha_aux))
    {
        float valor = desempilhar(&pilha_aux, erro);
        empilhar(destino, valor, erro);
        if (*erro != 0)
            return;
    }
}

void imprimir_pilha(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 1;
        return; // Caso a pilha esteja vazia, retorna e o erro é atualizado
    }

    // Ponteiro auxiliar para não modificar o ponteiro 'topo'
    No_Pilha *aux = P->topo;

    // Enquanto houver pilha para percorrer, imprime o lance
    // e avança para o próximo
    while (aux != NULL)
    {
        printf("%f\n", aux->valor);
        aux = aux->prox;
    }
    *erro = 0;
}

// Função que imprime apenas o topo da pilha (apenas o lance mais alto)
void imprimir_topo(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 1;
        return; // Caso a pilha esteja vazia, retorna e o erro é atualizado
    }

    // Imprime apenas o valor do topo da pilha
    printf("%f\n", P->topo->valor);
    *erro = 0;
}

// Função que apaga todos os nós da pilha
void excluir_pilha(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 1;
        return; // Caso a pilha esteja vazia, retorna e o erro é atualizado
    }

    // Ponteiros auxiliares
    No_Pilha *atual = P->topo;
    No_Pilha *temp = NULL;

    // Percorre a pilha e libera cada nó
    while (atual != NULL)
    {
        temp = atual;        // Guarda o nó atual para liberar
        atual = atual->prox; // Avança para o próximo nó
        free(temp);
    }
    P->topo = NULL; // Ajustando o ponteiro
    *erro = 0;
}