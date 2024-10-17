#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bloco{
    char *usuario;
    struct bloco *prox;
} No;

typedef struct{
    No *ini;
    No *fim;
    int total;
} Fila;


// Função que inicia a fila
void inicializar_fila(Fila *F) {
    F->ini = NULL;
    F->fim = NULL;
    F->total = 0;
}


// Função que verifica se a fila está vazia
// (retorna 1 se estiver vazia ou 0 se não estiver)
int fila_vazia(Fila *F) {
    return (F->total == 0);
}

// Função que insere um usuario na fila
void inserir_na_fila(Fila *F, char *nome_usuario, int *erro){

    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL){
        *erro = 1; 
        return;
    }

    novo->usuario = (char *)malloc((strlen(nome_usuario) + 1) * sizeof(char));
    if (novo->usuario == NULL) {
        free(novo);
        *erro = 1;
        return; // Caso a alocação falhe, libera o nó, retorna e o erro é atualizado 
    }
    
    // Copia o nome do usuario da variável temporária para a definitiva (campo da fila)
    strcpy(novo->usuario, nome_usuario); 
    novo->prox = NULL; // Atualiza o campo 'prox' do novo nó para nulo, até encontrar a posição correta

    if(F->ini == NULL){ // fila estava vazia, agora o novo usuario é o unico na fila
        F->ini=novo;
        F->fim=novo;
    }
    else{
        F->fim=novo;
        F->fim->prox=NULL; //ou recebe novo? Pq?
        // se for NULL mesmo, a linha acima é redundante por conta da linha abaixo de strcpy
    }
    F->total++;
    *erro = 0;
}

void remover_da_fila(Fila *F, char *nome_usuario, int *erro){
    
    if (fila_vazia(F)) {
        *erro = 4; // Atualiza o erro 
        return;    
    }
    
    No *aux = F->ini;
    F->ini = F->ini->prox;
    if(F->ini == NULL) // se agora o início da fila é nulo, o usuario excluido era o unico da fila, logo o fim deverá receber nulo também
        F->fim = NULL;
    free(aux);
    *erro = 0;
    F->total--;

    // nessa funcao, o professor declarou um ponteiro do tipo no auxiliar que recebe F->ini,
    // e posteriormente apenas dá free nesse aux
    // nao entendi mt bem qual a necessidade de passar isso pro aux se ele não é utilizado posteriormente
    // acredito que seria pro caso de querer saber qual elemento foi removido, porem sabendo que n deu erro,
    // conseguimos concluir q o elemento que passamos pra funcao foi removido.

}