/*
Os erros possuem diferentes códigos, para poderem ser tratados com precisão.
Desse modo, cabe ao usuário do TAD verificar o erro de acordo a função chamada.

função inserir_na_fila: 
    erro == 1 é falha na alocação 

função remover_da_fila:
    erro == 1 é fila vazia

função copiar_fila:
    erro == 1 é fila original vazia
    erro == 2 é fila destino já possui algum elemento (não está vazia)
    erro == 3 é falha na alocação ao chamar a função inserir_na_fila 
    
função inverter_fila:
    erro == 1 é fila original vazia
    erro == 2 é falha na alocação de algum nó
    erro == 3 é falha na alocação de algum nome

função excluir_fila:
    erro ==  1 é fila vazia

função esta_na_fila:
    erro == 1 é fila vazia
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
// (lembrar de excluir essa fila posteriormente); usa malloc
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
        F->fim->prox = novo; // Ajusta o ponteiro do "antigo" último elemento para apontar para o "novo" último elemento
    }
    F->fim = novo; // 'fim' sempre apontará para o novo elemento inserido
    *erro = 0;
}

// Função que remove o primeiro usuário da fila e devolve seu nome
char *remover_da_fila(Fila *F, int *erro) {
    if (fila_vazia(F)) {
        *erro = 1;
        return NULL; // Se a fila estiver vazia, retorna NULL e atualiza o erro
    }

    // Buffer temporário que retorna o nome
    char nome_aux[50];

    // Copia o nome do usuário da fila para o buffer
    strcpy(nome_aux, F->ini->usuario);

    // Ponteiro auxiliar para remover o nó
    No_Fila *aux = F->ini;
    F->ini = aux->prox;

    if (F->ini == NULL) {
        F->fim = NULL; // Se a fila ficou vazia após a remoção, atualiza o ponteiro 'fim'
    }

    free(aux->usuario); // Libera o nome do usuário 
    free(aux); // Libera o nó

    *erro = 0;
    return nome_aux; // Retorna o nome do usuário removido
}

// Função que copia todos os nós de uma fila para outra
void copiar_fila(Fila *fila_origem, Fila *fila_destino, int *erro) {
    if (fila_vazia(fila_origem)) {
        *erro = 1;
        return; // Verifica se a fila original está vazia
    }

    if (!fila_vazia(fila_destino)) {
        *erro = 2;
        return; // Verifica se a fila de destino contém algum elemento
    }

    // Ponteiro auxiliar para não alterar 'ini'
    No_Fila *no_aux = fila_origem->ini;

    // Percorre a fila original e copia os elementos para a fila destino
    while (no_aux != NULL) {
        inserir_na_fila(fila_destino, no_aux->usuario, erro);
        if (*erro) {
            *erro = 3;
            return; // Verifica se houve erro na alocação 
        } 
        no_aux = no_aux->prox;
    }
}

// Função que cria e retorna uma fila invertida (a partir da fila passada)
// (lembrar de excluir essa fila posteriormente); usa malloc
Fila inverter_fila(Fila *F, int *erro) {
    // Declarando e inicializando a nova fila invertida
    Fila fila_invertida;
    inicializar_fila(&fila_invertida); 

    if (fila_vazia(F)) {
        *erro = 1;
        return fila_invertida; // Se a fila original estiver vazia, retorna uma fila vazia e atualiza o erro
    }

    // Ponteiro auxiliar para não modificar 'ini'
    No_Fila *atual = F->ini;

    // Percorrendo a fila original 
    while (atual != NULL) {
        No_Fila *novo_no = (No_Fila *)malloc(sizeof(No_Fila));
        if (novo_no == NULL) {
            *erro = 2;
            return fila_invertida; // Se falhar retorna a fila, mas com erro sinalizado
        }

        novo_no->usuario = (char *)malloc((strlen(atual->usuario) + 1) * sizeof(char));
        if (novo_no->usuario == NULL) {
            *erro = 3;
            return fila_invertida; // Se falhar retorna a fila, mas com erro sinalizado
        }

        // Copiando os dados 
        strcpy(novo_no->usuario, atual->usuario);

        // Inserindo o novo nó no início da fila invertida e ajustando os ponteiros
        novo_no->prox = fila_invertida.ini; 
        fila_invertida.ini = novo_no;

        // Avançando para o próximo nó da fila original
        atual = atual->prox;
    }

    // O fim da fila invertida será o primeiro nó da fila original
    fila_invertida.fim = F->ini; 

    *erro = 0;
    return fila_invertida; // Retornamos a fila invertida
}

// Função que exclui todos os nós da fila
void excluir_fila(Fila *F, int *erro) {
    if (fila_vazia(F)) {
        *erro = 1;
        return; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Ponteiros auxiliares
    No_Fila *aux = F->ini;
    No_Fila *temp = NULL;

    while (aux != NULL) {
        temp = aux; // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó
        free(temp->usuario); // Libera o nome
        free(temp); // Libera o nó
    }

    // Ajustando os ponteiros
    F->ini = NULL;
    F->fim = NULL; 
    *erro = 0;
}

// Função que verifica se um nome está na fila
// (retorna 1 se estiver ou 0 se não estiver)
int esta_na_fila(Fila *F, char *nome, int *erro) {
    if (fila_vazia(F)) {
        *erro = 1;
        return 0; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Ponteiro auxiliar para não modificar 'ini'
    No_Fila *aux = F->ini;

    // Percorre toda a fila
    while (aux != NULL) {
        if (strcmp(aux->usuario, nome) == 0) {
            *erro = 0;
            return 1; // Se encontrar o nome, retorna 1 (positivo)
        }
        aux = aux->prox;
    }

    *erro = 0;
    return 0; // Se não encontrar, retorna 0 (negativo)
}