/*
erro == 1 significa falha na alocação de memória (função inserir_na_fila)
erro == 2 significa fila vazia (função remover_da_fila)
erro == 3 significa fila vazia (função imprimir_fila)
erro == 4 significa fila vazia (função imprimir_primeiro_fila)
erro == 5 significa fila não inicializada (função excluir_fila)
*/
// Includes padrão
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Criando a struct que armazena o nome do usuário
typedef struct no{
    char *usuario;
    struct no *prox;
} No;

// Ponteiros de início e fim da fila de usuários
typedef struct{
    No *ini;
    No *fim;
} Fila;

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
void inserir_na_fila(Fila *F, char *nome_usuario, int *erro){
    No *novo = (No *)malloc(sizeof(No)); // Aloca memória para um novo Nó
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

    if (fila_vazia(F)) { // Verifica se a fila estava vazia
        F->ini=novo; // O novo usuario é o primeiro
    } else { // Se não estava vazia
        F->fim->prox = novo; // Ajusta o ponteiro do "antigo" último elemento 
                             // para apontar para o "novo" último elemento
    }
    F->fim=novo; // O novo nó sempre será inserido no fim (lógica FIFO)
    *erro = 0;
}

void remover_da_fila(Fila *F, int *erro){
    if (fila_vazia(F)) {
        *erro = 2;  
        return; // Atualiza o erro e retorna
    }
    
    // Pega o primeiro nó da fila (que será removido)
    No *aux = F->ini;
    // Atualiza o início da fila 
    F->ini = aux->prox;

    // Se após a remoção a fila ficar vazia, atualiza o ponteiro fim
    if (F->ini == NULL) {
        F->fim = NULL;
    }
    free(aux->usuario); // Libera a string alocada para o nome do usuário
    free(aux); // Libera o nó
    *erro = 0;
}

// Função que imprime todos os elementos da fila
void imprimir_fila(Fila *F, int *erro) {
    // Verifica se a fila está vazia
    if (fila_vazia(F)) {
        *erro = 3;  
        return; // Atualiza o erro e retorna
    }

    // Ponteiro auxiliar para não modificar o ponteiro 'ini' 
    No *aux = F->ini;

    // Enquanto houver fila para percorrer, imprime o nome do usuário
    // e avança para o próximo
    while (aux != NULL) {
        printf("%s\n", aux->usuario); 
        aux = aux->prox; 
    }
    *erro = 0; 
}

void imprimir_primeiro_fila(Fila *F, int *erro) {
    // Verifica se a fila está vazia
    if (fila_vazia(F)) {
        *erro = 4;  
        return; // Atualiza o erro e retorna
    }
    printf("%s\n", F->ini->usuario); // Imprime apenas o primeiro da fila
    *erro = 0;
}

// Função para apagar todos os nós da fila
void excluir_fila(Fila *F, int *erro) {
    if (F == NULL) {
        *erro = 5;  
        return; // Caso a fila não tenha sido inicializada, atualiza o erro e retorna
    }

    // Ponteiros auxiliares 
    No *aux = F->ini;
    No *temp = NULL;

    // Percorre a fila e libera cada nó
    while (aux != NULL) {
        temp = aux;  // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó
        free(temp->usuario); 
        free(temp); 
    }
    F->ini = NULL;
    F->fim = NULL; // Ajustando os ponteiros
    *erro = 0;
}