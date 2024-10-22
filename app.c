/*
erro == 1 significa erro de alocação de memória (função inserir_lista)
erro == 2 significa produto já existente (função inserir_produto)
erro == 3 significa produto não encontrado (função remover_produto)
erro == 4 significa lista vazia (função remover_produto)
erro == 5 significa lista vazia (função imprimir_lista)
erro == 6 significa lista vazia (função excluir_lista)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "pilha.h"
#include "fila.h"

// funcao cadastrar produto
void cadastrar_produto(Lista **produtos, int *erro)
{
    if (*produtos == NULL)                                    // verifica se o ponteiro é nulo
        *produtos = (Lista *)malloc(sizeof(Lista));           // se for, aloca a memória da lista
    if ((*produtos)->ini == NULL && (*produtos)->fim == NULL) // caso a lista esteja vazia, inicializa ela
        inicializar_lista(*produtos);

    char nome_produto[50];
    printf("Entre com o nome do produto: ");
    scanf("%s", nome_produto);

    inserir_na_lista(*produtos, nome_produto, erro); // ERRO!!!!!!!!!!!!!!!!!!! esta matando o terminal assim que cai aqui

    if (*erro) // caso haja algum erro, retorna
        return;

    printf("Produto cadastrado com sucesso!\n");
    return;
}

/*
//funcao listar produtos  ***Tem que ser chamada junto com a funcao listar lances
void listar_produtos()

//funcao listar lances  ***Tem que ser chamada junto com a funcao listar produtos
void listar_lances()
*/

// funcao dar lance !!!!!!!!!!!!!!!!Função não testada
void dar_lance(Lista *produtos, int *erro)
{
    char nome[50], nome_produto[50];
    float valor;

    printf("Entre com seu nome: ");
    scanf("%s", nome);
    printf("Entre com o valor do lance: R$ ");
    scanf("%f", &valor);
    printf("Entre com o nome do produto: ");
    scanf("%s", nome_produto);

    if (!esta_na_lista(produtos, nome_produto, erro))
    {
        *erro = 3;
        return;
    }

    No1 *no_produto = acha_produto(produtos, nome_produto, erro);

    if (no_produto->usuarios_lances == NULL && no_produto->lances == NULL)
    {
        no_produto->usuarios_lances = (Fila *)malloc(sizeof(Fila));
        no_produto->lances = (Pilha *)malloc(sizeof(Pilha));
        if (no_produto->usuarios_lances == NULL || no_produto->lances == NULL)
        {
            *erro = 1;
            return;
        }
        inicializar_fila(no_produto->usuarios_lances);
        inicializar_pilha(no_produto->lances);
    }

    inserir_na_fila(no_produto->usuarios_lances, nome, erro);
    empilhar(no_produto->lances, valor, erro);

    printf("Lance dado com sucesso!\n");
    return;
}

/*
//funcao listar outros produtos
void listar_outros_produtos()
*/

// funcao remover produto
void remover_produto(Lista *produtos, int *erro)
{

    char nome_produto[50];
    printf("Nome do produto a remover: ");
    scanf("%s", nome_produto);

    if (!esta_na_lista(produtos, nome_produto, erro))
    {
        *erro = 3;
        return;
    }
    remover_da_lista(produtos, nome_produto, erro);

    if (*erro) // caso haja algum erro, retorna
        return;

    printf("Produto removido com sucesso!\n");
    return;
}

// funcao encerrar leilao
void encerrar_leilao(Lista *produtos, int *erro)
{
    excluir_lista(produtos, erro);
}

int main()
{
    Lista *produtos;
    int erro = 0;
    int opcao = 0;
    while (opcao != 6)
    {
        printf("Caro usuário, suas opcoes sao:\n");
        printf("1) Cadastrar um produto\n");
        printf("2) Listar produtos e lances\n");
        printf("3) Dar um lance\n");
        printf("4) Listar outros produtos disponiveis\n");
        printf("5) Remover produto\n");
        printf("6) Encerrar leilao\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            cadastrar_produto(&produtos, &erro);
            switch (erro)
            {
            case 1:
                printf("Errro de alocação de memória\n");
                break;
            case 2:
                printf("Produto já existente\n");
                break;
            }
        }
        else if (opcao == 2)
        {
            // listar_produtos();
        }
        else if (opcao == 3)
        {
            dar_lance(produtos, &erro);
            switch (erro)
            {
            case 1:
                printf("Errro de alocação de memória\n");
                break;
            case 3:
                printf("Produto não encontrado\n");
                break;
            }
        }
        else if (opcao == 4)
        {
            // listar_outros_produtos();
        }
        else if (opcao == 5)
        {

            remover_produto(produtos, &erro);
            switch (erro)
            {
            case 1:
                printf("Errro de alocação de memória\n");
                break;
            case 3:
                printf("Produto não encontrado\n");
                break;
            }
        }
        else if (opcao == 6)
        {
            encerrar_leilao(produtos, &erro);
        }
        else
        {
            printf("Opcao invalida! Digite uma das opcoes disponiveis\n");
        }
    }

    return 0;
}