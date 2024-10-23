/*
Caso haja algum erro em qualquer função, a função retorna 1. 
Desse modo, cabe ao usuário do TAD verificar o motivo do erro, 
de acordo a função chamada.
*/

// Includes padrão
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Função que inicializa a fila
void inicializar_fila(Fila *F) {
    F->ini = NULL;
    F->fim = NULL;
}


// Função que verifica se a fila está vazia
// (retorna 1 se estiver vazia ou 0 se não estiver)
int fila_vazia(Fila *F) {
    return (F->ini == NULL);
}


// Função que insere um usuario na fila
void inserir_na_fila(Fila *F, char *nome_usuario, int *erro) {
    No_Fila *novo = (No_Fila *)malloc(sizeof(No_Fila)); // Aloca memória para um novo Nó
    if (novo == NULL) {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // Aloca memória para o nome do usuário
    novo->usuario = (char *)malloc((strlen(nome_usuario) + 1) * sizeof(char));
    if (novo->usuario == NULL) {
        free(novo);
        *erro = 1;
        return; // Caso a alocação falhe, libera o nó, retorna e o erro é atualizado
    }

    // Copia o nome do usuário da variável temporária para a definitiva (campo da fila)
    strcpy(novo->usuario, nome_usuario); 

    novo->prox = NULL; // Sempre aponta para NULL, pois sempre é inserido no fim

    if (fila_vazia(F)) {                  
        F->ini = novo; // Se a fila estiver vazia, novo usuario é o primeiro
    } else {          
        // Ajusta o ponteiro do "antigo" último elemento para apontar para o "novo" último elemento              
        F->fim->prox = novo; 
    }
    F->fim = novo; // O novo nó sempre será inserido no fim (lógica FIFO)
    *erro = 0;
}


<<<<<<< Updated upstream
// Função que remove o pirmeiro usuário da fila e devolve seu nome
char *remover_da_fila(Fila *F, int *erro) {
=======
// Função que remove o primeiro usuário da fila (simplesmente apaga o nó)
void remover_da_fila(Fila *F, int *erro) {
>>>>>>> Stashed changes
    if (fila_vazia(F)) {
        *erro = 1;
        return; // Se a fila estiver vazia, retorna e o erro é atualizado
    }
    char nome_aux[50];
    nome_aux = F->ini->nome_usuario;
    // Ponteiro auxiliar para remover 
    No_Fila *aux = F->ini;
    F->ini = aux->prox;

    if (F->ini == NULL) {
        F->fim = NULL; // Se após a remoção a fila ficar vazia, atualiza o ponteiro fim
    }
    free(aux->usuario); // Libera o nome do usuário
    free(aux); // Libera o nó
    *erro = 0;
    return(nome_aux);
}


// Função que imprime todos os elementos da fila
void imprimir_fila(Fila *F, int *erro) {
    if (fila_vazia(F)) {
        *erro = 1;
        return; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Ponteiro auxiliar para não modificar o ponteiro 'ini'
    No_Fila *aux = F->ini;

    // Enquanto houver fila para percorrer, imprime o nome do usuário
    // e avança para o próximo
    while (aux != NULL) {
        printf("%s\n", aux->usuario);
        aux = aux->prox;
    }
    *erro = 0;
}

void imprimir_primeiro_fila(Fila *F, int *erro) {
    if (fila_vazia(F)) {
        *erro = 1;
        return; // Se a fila estiver vazia, retorna e o erro é atualizado
    }
    printf("%s\n", F->ini->usuario); // Imprime apenas o primeiro da fila
    *erro = 0;
}


// Função para apagar todos os nós da fila
void excluir_fila(Fila *F, int *erro) {
    if (fila_vazia(F)) {
        *erro = 1;
        return; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Ponteiros auxiliares
    No_Fila *aux = F->ini;
    No_Fila *temp = NULL;

    // Percorre a fila e libera cada nó
    while (aux != NULL) {
        temp = aux; // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó
        free(temp->usuario);
        free(temp);
    }
    F->ini = NULL;
    F->fim = NULL; // Ajustando os ponteiros
    *erro = 0;
}