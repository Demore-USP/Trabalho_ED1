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
void inicializar_fila(Fila *F)
{
    F->ini = NULL;
    F->fim = NULL;
}

// Função que verifica se a fila está vazia
// (retorna 1 se estiver vazia ou 0 se não estiver)
int fila_vazia(Fila *F)
{
    return (F->ini == NULL);
}

// Função que insere um usuario na fila
void inserir_na_fila(Fila *F, char *nome_usuario, int *erro)
{
    No_Fila *novo = (No_Fila *)malloc(sizeof(No_Fila)); // Aloca memória para um novo Nó
    if (novo == NULL)
    {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // Aloca memória para o nome do usuário
    novo->usuario = (char *)malloc((strlen(nome_usuario) + 1) * sizeof(char));
    if (novo->usuario == NULL)
    {
        free(novo);
        *erro = 1;
        return; // Caso a alocação falhe, libera o nó, retorna e o erro é atualizado
    }

    // Copia o nome do usuário da variável temporária para a definitiva (campo da fila)
    strcpy(novo->usuario, nome_usuario);

    novo->prox = NULL; // Sempre aponta para NULL, pois sempre é inserido no fim

    if (fila_vazia(F))
    {
        F->ini = novo; // Se a fila estiver vazia, novo usuario é o primeiro
    }
    else
    {
        // Ajusta o ponteiro do "antigo" último elemento para apontar para o "novo" último elemento
        F->fim->prox = novo;
    }
    F->fim = novo; // O novo nó sempre será inserido no fim (lógica FIFO)
    *erro = 0;
}

// Função que remove o pirmeiro usuário da fila e devolve seu nome
char *remover_da_fila(Fila *F, int *erro)
{
    // Verifica se a fila está vazia
    if (fila_vazia(F))
    {
        *erro = 1;
        return NULL; // Se a fila estiver vazia, retorna NULL e atualiza o erro
    }

    // Aloca espaço para armazenar o nome do usuário removido
    char *nome_aux = (char *)malloc(strlen(F->ini->usuario) + 1);
    if (nome_aux == NULL)
    {
        *erro = 2; // Erro de alocação de memória
        return NULL;
    }

    // Copia o nome do usuário da fila para a variável auxiliar
    strcpy(nome_aux, F->ini->usuario);

    // Ponteiro auxiliar para remover o nó
    No_Fila *aux = F->ini;
    F->ini = aux->prox;

    // Se a fila ficou vazia após a remoção, atualiza o ponteiro 'fim'
    if (F->ini == NULL)
    {
        F->fim = NULL;
    }

    // Libera a memória alocada para o nome e o nó
    free(aux->usuario); // Libera o nome do usuário no nó removido
    free(aux);          // Libera o nó

    *erro = 0;       // Nenhum erro
    return nome_aux; // Retorna o nome do usuário removido
}

void copiar_fila(Fila *origem, Fila *destino, int *erro)
{
    if (fila_vazia(origem))
    {
        *erro = 1;
        return;
    }

    No_Fila *no_fila = origem->ini;

    // Percorre a fila original e copia os elementos para a fila destino
    while (no_fila != NULL)
    {
        inserir_na_fila(destino, no_fila->usuario, erro);
        if (*erro != 0)
            return;
        no_fila = no_fila->prox;
    }
}

// Função que imprime todos os elementos da fila
void imprimir_fila(Fila *F, int *erro)
{
    if (fila_vazia(F))
    {
        *erro = 1;
        return; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Ponteiro auxiliar para não modificar o ponteiro 'ini'
    No_Fila *aux = F->ini;

    // Enquanto houver fila para percorrer, imprime o nome do usuário
    // e avança para o próximo
    while (aux != NULL)
    {
        printf("%s\n", aux->usuario);
        aux = aux->prox;
    }
    *erro = 0;
}

void imprimir_primeiro_fila(Fila *F, int *erro)
{
    if (fila_vazia(F))
    {
        *erro = 1;
        return; // Se a fila estiver vazia, retorna e o erro é atualizado
    }
    printf("%s\n", F->ini->usuario); // Imprime apenas o primeiro da fila
    *erro = 0;
}

Fila inverter_fila(Fila *F, int *erro)
{
    Fila fila_invertida;
    inicializar_fila(&fila_invertida); // Inicializamos a nova fila invertida

    if (fila_vazia(F))
    {
        return fila_invertida; // Se a fila original estiver vazia, retornamos uma fila vazia
    }

    No_Fila *atual = F->ini;

    // Percorremos a fila original do início ao fim
    while (atual != NULL)
    {
        // Criamos um novo nó com o mesmo conteúdo do nó atual da fila original
        No_Fila *novo_no = (No_Fila *)malloc(sizeof(No_Fila));
        if (novo_no == NULL)
        {
            printf("Erro de alocação de memória.\n");
            exit(1); // Se falhar a alocação, terminamos o programa
        }
        novo_no->usuario = (char *)malloc((strlen(atual->usuario) + 1) * sizeof(char));
        if (novo_no->usuario == NULL)
        {
            printf("Erro de alocação de memória.\n");
            exit(1);
        }

        // Copia os dados do nó atual da fila original para o novo nó
        strcpy(novo_no->usuario, atual->usuario);
        novo_no->prox = fila_invertida.ini; // Inserimos o novo nó no início da fila invertida
        fila_invertida.ini = novo_no;

        // Avançamos para o próximo nó da fila original
        atual = atual->prox;
    }

    // Após o loop, ajustamos o ponteiro para o fim da fila invertida
    fila_invertida.fim = F->ini; // O fim da fila invertida será o primeiro nó da fila original

    return fila_invertida; // Retornamos a fila invertida
}

// Função para apagar todos os nós da fila
void excluir_fila(Fila *F, int *erro)
{
    if (fila_vazia(F))
    {
        *erro = 1;
        return; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Ponteiros auxiliares
    No_Fila *aux = F->ini;
    No_Fila *temp = NULL;

    // Percorre a fila e libera cada nó
    while (aux != NULL)
    {
        temp = aux;      // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó
        free(temp->usuario);
        free(temp);
    }
    F->ini = NULL;
    F->fim = NULL; // Ajustando os ponteiros
    *erro = 0;
}

int esta_na_fila(Fila *F, char *nome, int *erro) {
    if (fila_vazia(F)) {
        *erro = 1;
        return; // Se a fila estiver vazia, retorna e o erro é atualizado
    }

    // Ponteiro auxiliar para não modificar 'ini'
    No_Fila *aux = F->ini;

    while(aux != NULL) {
        if(strcmp(aux->usuario, nome) == 0) {
            *erro = 0;
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}