#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "fila.h"
#include "pilha.h"

// Função que cadastra um produto na lista
void cadastrar_produto(Lista *lista_de_produtos, int *erro) {
    char nome_produto[50];
    printf("Entre com o nome do produto: ");
    scanf("%s", nome_produto);

    inserir_produto_lista(lista_de_produtos, nome_produto, erro); 

    if (*erro) 
        return; // caso haja algum erro, retorna

    printf("Produto cadastrado com sucesso!\n");
    return;
}

//funcao_listar_produtos_lances  ***Tem que ser chamada junto com a funcao listar lances
void listar_produtos_lances(Lista *lista_de_produtos, int *erro) {

    if(*erro)
        return;

    printf("Listagem completa!");
    return;
}

// funcao dar lance !!!!!!!!!!!!!!!!Função não testada
void dar_lance(Lista *lista_de_produtos, int *erro) {
    char nome_usuario[50], nome_produto[50];
    float valor;

    printf("Entre com seu nome: ");
    scanf("%s", nome_usuario);
    printf("\nEntre com o valor do lance: R$ ");
    scanf("%f", &valor);
    printf("\nEntre com o nome do produto: ");
    scanf("%s", nome_produto);

    inserir_lance(lista_de_produtos, nome_produto, valor, nome_usuario, erro);

    printf("\nLance dado com sucesso!\n");
    return;
}

/*
//funcao listar outros produtos
void listar_outros_produtos()
*/

// funcao remover produto
void remover_produto(Lista *lista_de_produtos, int *erro) {

    // Recebendo o nome do produto
    char nome_produto[50];
    printf("Nome do produto a remover: ");
    scanf("%s", nome_produto);

    remover_da_lista(lista_de_produtos, nome_produto, erro);
    if (*erro) 
        return; // Caso haja algum erro, retorna

    printf("Produto removido com sucesso!\n");
    return;
}

// funcao encerrar leilao
void encerrar_leilao(Lista *produtos, int *erro) {
    excluir_lista(produtos, erro);
}

int main() {

    Lista lista_de_produtos;
    Fila usuarios_geral;
    int erro = 0;
    int opcao = 0;

    inicializar_lista(&lista_de_produtos);

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
            cadastrar_produto(&lista_de_produtos, &erro);
            switch (erro) {
            case 1:
                printf("Erro de alocação de memória\n");
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
            dar_lance(&lista_de_produtos, &erro);
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

            remover_produto(&lista_de_produtos, &erro);
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
            encerrar_leilao(&lista_de_produtos, &erro);
        }
        else
        {
            printf("Opcao invalida! Digite uma das opcoes disponiveis\n");
        }
    }

    return 0;
}