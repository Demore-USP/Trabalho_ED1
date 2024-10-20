/*
erro == 1 significa erro de alocação de memória
erro == 2 significa pilha vazia (função desempilhar)
erro == 3 significa pilha vazia (função imprimir_toda_pilha)
erro == 4 significa pilha vazia (função imprimir_topo)
erro == 5 significa pilha não inicializada (função excluir_pilha)
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
    No2 *novo = (No2 *)malloc(sizeof(No2)); // Aloca memória para um novo Nó
    if (novo == NULL)
    {
        *erro = 1;
        return; // // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // O novo lance aponta para o lance anterior (antigo topo), e o topo
    // passa a apontar para o novo lance
    novo->valor = valor;
    novo->prox = P->topo;
    P->topo = novo;
    *erro = 0;
}

// Função que remove o último lance da pilha (simplesmente apaga o nó)
void desempilhar(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 2;
        // Se a pilha estiver vazia é impossível remover algo, então
        // atualiza o erro e retorna
        return;
    }

    No2 *temp = P->topo;
    P->topo = P->topo->prox;
    free(temp);
    *erro = 0;
}

void imprimir_pilha(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 3;
        return; // Se a pilha estiver vazia, atualiza o erro e retorna
    }

    // Ponteiro auxiliar para não modificar o ponteiro topo
    No2 *atual = P->topo;

    // Enquanto houver pilha para percorrer, imprime o lance
    // e avança para o próximo
    while (atual != NULL)
    {
        printf("%f\n", atual->valor);
        atual = atual->prox;
    }

    *erro = 0;
}

// Função que imprime apenas o topo da pilha (apenas o lance mais alto)
void imprimir_topo(Pilha *P, int *erro)
{
    if (pilha_vazia(P))
    {
        *erro = 4;
        return; // Se a pilha estiver vazia, atualiza o erro e retorna
    }

    // Imprime apenas o valor do topo da pilha
    printf("%f\n", P->topo->valor);
    *erro = 0;
}

// Função que apaga todos os nós da pilha
void excluir_pilha(Pilha *P, int *erro)
{
    if (P == NULL)
    {
        *erro = 5;
        return; // Caso a pilha não tenha sido inicializada, atualiza o erro e retorna
    }

    // Ponteiros auxiliares
    No2 *atual = P->topo;
    No2 *temp = NULL;

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