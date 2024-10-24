/*
Caso haja erro com alguma função da lista, retorna 1.
Caso haja erro com alguma função da fila, retorna 2.
Caso haja erro com alguma função da pilha, retorna 3.
Desse modo, cabe ao usuário do TAD verificar o motivo do erro,
de acordo a função chamada.
*/

// Includes padrão
#include "lista.h"
#include "fila.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que inicializa a lista
void inicializar_lista(Lista *L)
{
    L->ini = NULL;
    L->fim = NULL;
}

// Função que verifica se a lista está vazia
// (retorna 1 se está vazia ou 0 se não está)
int lista_vazia(Lista *L)
{
    return (L->ini == NULL);
}

// Função que insere um produto na lista
// (já implementada com inserção em ordem alfabética)
void inserir_produto_lista(Lista *L, char *nome_produto, int *erro)
{
    No_Lista *novo = (No_Lista *)malloc(sizeof(No_Lista)); // Aloca memória para um novo Nó
    if (novo == NULL)
    {
        *erro = 1;
        return; // Caso a alocação falhe, retorna e o erro é atualizado
    }

    // Aloca memória para o nome do produto
    novo->produto = (char *)malloc((strlen(nome_produto) + 1) * sizeof(char));
    if (novo->produto == NULL)
    {
        free(novo->produto);
        free(novo);
        *erro = 1;
        return; // Caso a alocação falhe, libera o nó, retorna e o erro é atualizado
    }

    // Copia o nome do produto da variável temporária para a definitiva (campo da lista)
    strcpy(novo->produto, nome_produto);

    inicializar_fila(&novo->usuarios); // Inicializa a fila de usuários
    inicializar_pilha(&novo->lances);  // Inicializa a pilha de lances

    novo->prox = NULL; // Atualiza o campo 'prox' do novo nó para nulo, até encontrar a posição correta

    // Cria dois ponteiros auxiliares, para achar qual posição
    // o novo produto assumirá
    No_Lista *ant = NULL;
    No_Lista *aux = L->ini;

    // Enquanto o ponteiro auxiliar for != de nulo, ou seja, enquanto houver lista para percorrer,
    // e enquanto o produto a ser inserido for lexicograficamente maior, percorre a lista.
    // Quando a condição for quebrada, 'aux' apontará para o elemento que ficará à frente do novo produto,
    // e 'ant' apontará para o anterior do novo produto
    while (aux != NULL && strcmp(aux->produto, nome_produto) < 0)
    {
        ant = aux;
        aux = aux->prox;
    }

    // Verifica se o produto já existe
    if (aux != NULL && strcmp(aux->produto, nome_produto) == 0)
    {
        *erro = 1;
        free(novo->produto);
        free(novo);
        return;
    }
    if (ant == NULL)
    { // Se for o primeiro da lista
        novo->prox = L->ini;
        L->ini = novo;
    }
    else
    { // Se não for
        ant->prox = novo;
        novo->prox = aux;
    }

    if (aux == NULL)
    { // Verifica se o novo produto será o último elemento da lista
        L->fim = novo;
    }
    *erro = 0; // Atualiza o erro
}

// Função que procura um produto específico e retorna um ponteiro para ele
No_Lista *procurar_produto(Lista *L, char *nome_produto, int *erro)
{
    if (lista_vazia(L))
    {
        *erro = 1;
        return NULL; // Caso a lista esteja vazia, retorna NULL e o erro é atualizado
    }

    // Ponteiro auxiliar para não modificar o ponteiro 'ini'
    No_Lista *aux = L->ini;

    // Enquanto houver lista para percorrer
    while (aux != NULL)
    {
        // Caso entre no 'if', o produto foi encontrado
        if (strcmp(aux->produto, nome_produto) == 0)
        {
            *erro = 0;
            return aux;
        }
        aux = aux->prox;
    }

    *erro = 1;
    return NULL; // Se o produto não foi encontrado, retorna NULL e o erro é atualizado
}

// Função que verifica se um produto esta na lista
// (Verificação de erro desnecessária)
int esta_na_lista(Lista *L, char *nome_produto, int *erro)
{
    if (procurar_produto(L, nome_produto, erro) != NULL)
        return 1;
    return 0;
}

// Função que remove um produto da lista (simplesmente apaga um nó)
void remover_da_lista(Lista *L, char *nome_produto, int *erro)
{
    if (lista_vazia(L))
    {
        *erro = 1; // Caso a lista esteja vazia, retorna e o erro é atualizado
        return;
    }

    if (!esta_na_lista(L, nome_produto, erro))
    {
        *erro = 1;
        return; // Caso o produto não esteja na lista, retorna e o erro é atualizado
    }

    // Cria dois ponteiros auxiliares
    No_Lista *ant = NULL;
    No_Lista *aux = L->ini;

    /* Enquanto houver lista para percorrer e enquanto os nomes não
    forem idênticos, percorre a lista.
    Quando a condição for quebrada, 'aux' apontará para o produto a ser removido,
    e 'ant' apontará para o produto anterior */
    while (aux != NULL && strcmp(aux->produto, nome_produto) != 0)
    {
        ant = aux;
        aux = aux->prox;
    }

    if (ant == NULL)
    {
        L->ini = aux->prox; // Se o produto a ser removido for o primeiro da lista
    }
    else
    {
        ant->prox = aux->prox; // Se não for
    }

    if (aux == L->fim)
    {
        L->fim = ant; // Se o produto a ser removido for o último da lista
    }

    // Se a fila não estiver vazia, é excluída
    if (!fila_vazia(&aux->usuarios))
    {
        excluir_fila(&aux->usuarios, erro);
        if (*erro)
            *erro = 2;
        return;
    }

    // Se a pilha não estiver vazia, é excluída
    if (!pilha_vazia(&aux->lances))
    {
        excluir_pilha(&aux->lances, erro);
        if (*erro)
            *erro = 3;
        return;
    }

    free(aux->produto); // Libera o nome
    free(aux);          // Libera o nó
    *erro = 0;
}

// Função que imprime todos os produtos da lista
void imprimir_produtos(Lista *L, int *erro)
{
    if (lista_vazia(L))
    {
        *erro = 1;
        return; // Caso a lista esteja vazia, retorna e o erro é atualizado
    }

    // Ponteiro auxiliar para não modificar o ponteiro 'ini'
    No_Lista *aux = L->ini;

    // Enquanto houver lista para percorrer, imprime o nome do produto
    // e avança para o próximo
    while (aux != NULL)
    {
        printf("%s\n", aux->produto);
        aux = aux->prox;
    }

    *erro = 0;
}

// Função para apagar todos os nós da lista
void excluir_lista(Lista *L, int *erro)
{
    if (lista_vazia(L))
    {
        *erro = 1;
        return; // Caso a lista esteja vazia, atualiza o erro e retorna
    }

    // Ponteiros auxiliares
    No_Lista *aux = L->ini;
    No_Lista *temp = NULL;

    // Percorre a lista e libera cada nó
    while (aux != NULL)
    {
        temp = aux;      // Guarda o nó atual para liberar
        aux = aux->prox; // Avança para o próximo nó

        // Se a fila não estiver vazia, é excluída
        if (!fila_vazia(&temp->usuarios))
        {
            excluir_fila(&temp->usuarios, erro);
            if (*erro)
            {
                *erro = 2;
                return;
            }
        }

        // Se a pilha não estiver vazia, é excluída
        if (!pilha_vazia(&temp->lances))
        {
            excluir_pilha(&temp->lances, erro);
            if (*erro)
            {
                *erro = 3;
                return;
            }
        }

        free(temp->produto); // Libera o produto
        free(temp);          // Libera o nó atual
    }

    // Após liberar tudo, ajusta os ponteiros
    L->ini = NULL;
    L->fim = NULL;
    *erro = 0;
}

void inserir_lance(Lista *L, char *nome_produto, float valor, char *nome_usuario, int *erro)
{
    // Procurando o produto a dar lance
    No_Lista *aux = procurar_produto(L, nome_produto, erro);
    if (*erro || aux == NULL)
        return;

    inserir_na_fila(&aux->usuarios, nome_usuario, erro);
    empilhar(&aux->lances, valor, erro);
    if (*erro)
        return;

    *erro = 0;
}

char *buscar_produto_especifico(Lista *L, int indice, int *erro)
{
    if (lista_vazia(L))
    {
        *erro = 1;
        return NULL; // Caso a lista esteja vazia, retorna e o erro é atualizado
    }

    // Ponteiro auxiliar para não modificar o ponteiro 'ini'
    No_Lista *aux = L->ini;
    int i = 0;
    // Enquanto houver lista para percorrer, imprime o nome do produto
    // e avança para o próximo
    while (aux != NULL)
    {
        if (i == indice)
        {
            return aux->produto;
        }
        i++;
        aux = aux->prox;
    }

    *erro = 1;
    return NULL;
}

char *buscar_usuario_ganhador(Lista *L, int indice, int *erro)
{
    if (lista_vazia(L))
    {
        *erro = 1;
        return NULL; // Se a lista de produtos estiver vazia
    }

    No_Lista *produto_atual = L->ini;
    int i = 0;

    // Percorre a lista até encontrar o produto de índice 'indice'
    while (produto_atual != NULL)
    {
        if (i == indice)
        {
            // Encontrou o produto, agora busca o ganhador

            if (fila_vazia(&produto_atual->usuarios))
            {
                *erro = 1; // Nenhum usuário na fila, sem lances
                return NULL;
            }
            // Obtemos a fila invertida, sem alterar a original
            Fila fila_invertida = inverter_fila(&produto_atual->usuarios, erro);

            Fila *fila_usuarios = &fila_invertida;
            No_Fila *no_usuario = fila_usuarios->ini;
            No_Pilha *no_lance = produto_atual->lances.topo; // Pegamos o lance mais recente do topo da pilha

            No_Fila *ganhador = no_usuario;      // Inicialmente assume o primeiro usuário como ganhador
            float maior_lance = no_lance->valor; // O lance mais alto começa sendo o primeiro

            // Percorrer a fila de usuários e pilha de lances simultaneamente
            while (no_usuario != NULL && no_lance != NULL)
            {
                if (no_lance->valor == maior_lance)
                {
                    ganhador = no_usuario; // Atualiza o ganhador
                }

                no_usuario = no_usuario->prox;
                no_lance = no_lance->prox; // Avança para o próximo lance
            }

            // Retorna o nome do ganhador
            *erro = 0;
            return ganhador->usuario;
        }

        produto_atual = produto_atual->prox; // Avança para o próximo produto
        i++;
    }

    *erro = 1; // Produto não encontrado
    return NULL;
}

float buscar_maior_lance(Lista *lista_de_produtos, int indice, int *erro)
{
    // Verifica se a lista está vazia
    if (lista_vazia(lista_de_produtos))
    {
        *erro = 1; // Erro: Lista vazia
        return 0.0;
    }

    No_Lista *produto_atual = lista_de_produtos->ini;
    int i = 0;

    // Percorre a lista até encontrar o produto correspondente ao índice
    while (produto_atual != NULL && i < indice)
    {
        produto_atual = produto_atual->prox;
        i++;
    }

    // Verifica se o produto foi encontrado
    if (produto_atual == NULL || i != indice)
    {
        *erro = 1; // Erro: Produto não encontrado
        return 0.0;
    }

    // Verifica se a pilha de lances está vazia
    if (pilha_vazia(&produto_atual->lances))
    {
        *erro = 3; // Erro: Não há lances para este produto
        return 0.0;
    }

    // Retorna o valor do maior lance (valor no topo da pilha)
    return produto_atual->lances.topo->valor;
}

int numero_de_produtos(Lista *L, int *erro)
{
    // verificando se a lista está vazia
    if (lista_vazia(L))
    {
        *erro = 1;
        return 0;
    }
    else
    {
        int i = 0;
        No_Lista *aux = L->ini;
        while (aux != NULL)
        {
            i++;
            aux = aux->prox;
        }
        return i;
    }
}
int buscar_indice_produto(Lista *L, char *nome_produto, int *erro)
{
    if (lista_vazia(L))
    {
        *erro = 1;
        return -1;
    }
    No_Lista *aux = L->ini;
    int i = 0;
    while (aux != NULL)
    {
        if (strcmp(aux->produto, nome_produto) == 0)
        {
            *erro = 0;
            return i;
        }
        i++;
        aux = aux->prox;
    }
    *erro = 1;
    return -1;
}