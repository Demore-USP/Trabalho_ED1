/*
erro == 1 significa erro de alocação de memória (função inserir_lista)
erro == 2 significa produto já existente (função inserir_produto)
erro == 3 significa produto não encontrado (função remover_produto)
erro == 4 significa lista vazia (função remover_produto)
erro == 5 significa lista vazia (função imprimir_lista)
erro == 6 significa lista não inicializada (função excluir_lista)
*/

// Includes padrão
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Criando a struct que armazena os produtos (por nome)
typedef struct no {
    char *produto;
    struct no *prox;
} No;

// Ponteiros de início e fim da lista de produtos
typedef struct {
    No *ini;
    No *fim;
} Lista;

// Função que inicializa a lista
void inicializar_lista(Lista *L) {
    L->ini = NULL;
    L->fim = NULL;
}

// Função que verifica se a lista está vazia
// (retorna 1 se está vazia ou 0 se não está)
int lista_vazia(Lista *L) {
    return (L->ini == NULL);
}

// Função que insere um produto na lista 
// (já implementada com inserção em ordem alfabética)
void inserir_na_lista(Lista *L, char *nome_produto, int *erro) {
    No *novo = (No *)malloc(sizeof(No)); // Aloca memória para um novo Nó
    if (novo == NULL) {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado 
    }
    // Aloca memória para o nome do produto
    novo->produto = (char *)malloc((strlen(nome_produto) + 1) * sizeof(char));
    if (novo->produto == NULL) {
        free(novo);
        *erro = 1;
        return; // Caso a alocação falhe, libera o nó, retorna e o erro é atualizado 
    }
    // Copia o nome do produto da variável temporária para a definitiva (campo da lista)
    strcpy(novo->produto, nome_produto); 
    novo->prox = NULL; // Atualiza o campo 'prox' do novo nó para nulo, até encontrar a posição correta

    // Cria dois ponteiros auxiliares, para achar qual posição
    // o novo produto assumirá
    No *ant = NULL;
    No *aux = L->ini;

    // Enquanto o ponteiro auxiliar for != de nulo, ou seja, enquanto houver lista para percorrer, 
    // e enquanto o produto a ser inserido for lexicograficamente maior, percorre a lista.
    // Quando a condição for quebrada, 'aux' apontará para o elemento que ficará a frente do novo produto, 
    // e 'ant' apontará para o anterior do novo produto 
    while (aux != NULL && strcmp(aux->produto, nome_produto) < 0) { 
        ant = aux;
        aux = aux->prox;
    }
    // Verifica se o produto já existe
    if (aux != NULL && strcmp(aux->produto, nome_produto) == 0) {
    *erro = 2; 
    free(novo->produto);
    free(novo);
    return;
    }
    if (ant == NULL) { // Verifica se o novo produto será o primeiro elemento da lista
        novo->prox = L->ini;
        L->ini = novo;
    } else { // Caso não seja o primeiro da lista, ajusta os ponteiros 
        ant->prox = novo;
        novo->prox = aux;
    }
    if (aux == NULL) { // Verifica se o novo produto será o último elemento da lista 
        L->fim = novo;
    }
    *erro = 0; // Atualiza o erro
}

// Função que remove um produto da lista (simplesmente apaga um nó)
void remover_da_lista(Lista *L, char *nome_produto, int *erro) {

    // Verifica se a lista está vazia
    if (lista_vazia(L)) {
        *erro = 4; // Atualiza o erro 
        return;    
    }

    // Novamente cria dois ponteiros auxiliares
    No *ant = NULL;
    No *aux = L->ini;

    // Enquanto houver lista para percorrer e enquanto os nomes não
    // forem idênticos, percorre a lista.
    // Quando a condição for quebrada, 'aux' apontará para o produto a ser removido,
    // e 'ant' apontará para o produto anterior
    while (aux != NULL && strcmp(aux->produto, nome_produto) != 0) {
        ant = aux;
        aux = aux->prox;
    }
    // Se aux for NULL, a lista foi percorrida completamente e 
    // o produto a ser removido não foi encontrado
    if (aux == NULL) {  
        *erro = 3;
        return; // Retorna erro pois o produto não foi encontrado (provavelmente não existe)
    }
    if (ant == NULL) { // Verifica se o produto a ser removido é o primeiro elemento da lista
        L->ini = aux->prox;
    } else { // Caso não for o primeiro da lista, ajusta os ponteiros 
        ant->prox = aux->prox;
    }
    if (aux == L->fim) { // Verifica se o produto a ser removido é o último elemento da lista
        L->fim = ant;
    }
    free(aux->produto); // Libera a memória alocada para o nome
    free(aux); // Libera o nó
    *erro = 0; // Atualiza o erro
}

// Função que imprime todos os elementos da lista
void imprimir_lista(Lista *L, int *erro) {
    // Verifica se a lista está vazia
    if (lista_vazia(L)) {
        *erro = 5; // Atualiza o erro 
        return;    
    }

    // Ponteiro auxiliar para não modificar os ponteiros 'ini' e 'fim'
    No *aux = L->ini;

    // Enquanto houver lista para percorrer, imprime o nome do produto
    // e avança para o próximo
    while (aux != NULL) {
        printf("%s\n", aux->produto); 
        aux = aux->prox; 
    }

    *erro = 0; 
}

// Função para apagar todos os nós da lista
void excluir_lista(Lista *L, int *erro) {
    if (L == NULL) {
        *erro = 6;  
        return; // Caso a lista não tenha sido inicializada, atualiza o erro e retorna
    }

    // Ponteiros auxiliares 
    No *aux = L->ini;
    No *temp = NULL;

    // Percorre a lista e libera cada nó
    while (aux != NULL) {
        temp = aux;  // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó
        free(temp->produto); 
        free(temp); 
    }
    *erro = 0;
}