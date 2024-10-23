// Includes padrão
#include "lista_simples.h"
#include "fila.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que inicializa a lista
void inicializar_Lista_simples(Lista_simples *L) {
    L->ini = NULL;
    L->fim = NULL; 
}


// Função que verifica se a lista está vazia
// (retorna 1 se está vazia ou 0 se não está)
int lista_vazia(Lista_simples *L) {
    return (L->ini == NULL);
}

// Função que insere um produto na lista
// (já implementada com inserção em ordem alfabética)
void inserir_produto_lista(Lista_simples *L, char *nome, int *erro) {
    No *novo = (No *)malloc(sizeof(No)); // Aloca memória para um novo Nó
    if (novo == NULL) {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // Aloca memória para o nome do produto
    novo->nome = (char *)malloc((strlen(nome) + 1) * sizeof(char));
    if (novo->nome == NULL) {
        free(novo->nome);
        free(novo);
        *erro = 1;
        return; // Caso a alocação falhe, libera o nó, retorna e o erro é atualizado
    }

    // Copia o nome do produto da variável temporária para a definitiva (campo da lista)
    strcpy(novo->nome, nome);

    novo->prox = NULL; // Atualiza o campo 'prox' do novo nó para nulo, até encontrar a posição correta

    // Cria dois ponteiros auxiliares, para achar qual posição
    // o novo produto assumirá
    No *ant = NULL;
    No *aux = L->ini;

    // Enquanto o ponteiro auxiliar for != de nulo, ou seja, enquanto houver lista para percorrer,
    // e enquanto o produto a ser inserido for lexicograficamente maior, percorre a lista.
    // Quando a condição for quebrada, 'aux' apontará para o elemento que ficará à frente do novo produto,
    // e 'ant' apontará para o anterior do novo produto
    while (aux != NULL && strcmp(aux->nome, nome) < 0) {
        ant = aux;
        aux = aux->prox;
    }

    // Verifica se o produto já existe
    if (aux != NULL && strcmp(aux->nome, nome) == 0) {
        *erro = 1;
        free(novo->nome);
        free(novo);
        return;
    }
    if (ant == NULL) { // Se for o primeiro da lista
        novo->prox = L->ini;
        L->ini = novo;
    } else { // Se não for
        ant->prox = novo;
        novo->prox = aux;
    }

    if (aux == NULL) { // Verifica se o novo produto será o último elemento da lista
        L->fim = novo;
    }
    *erro = 0; // Atualiza o erro
}