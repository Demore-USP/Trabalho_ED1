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
void cadastrar_produto(Lista *produtos, int *erro)
{
    char nome_produto[50];

    if (produtos->ini == NULL && produtos->fim == NULL) // ta travando aq, por algum motivo n ta avançado pro proximo printf, fé
        inicializar_lista(produtos);                    // dei uma alterada nos .h e .c mas não consegui resolver

    printf("Entre com o nome do produto: ");
    scanf("%s", nome_produto);

    inserir_na_lista(produtos, nome_produto, erro);

    if (*erro == 1)
        return;

    printf("Produto cadastrado com sucesso!\n");
    return;
}

/*
//funcao listar produtos  ***Tem que ser chamada junto com a funcao listar lances
void listar_produtos()

//funcao listar lances  ***Tem que ser chamada junto com a funcao listar produtos
void listar_lances()

//funcao dar lance
void dar_lance()

//funcao listar outros produtos
void listar_outros_produtos()

//funcao encerrar leilao
void encerrar_leilao()

//funcao remover produto
void remover_produto()
*/

int main()
{
    Lista *produtos = NULL;
    Pilha *lances = NULL;
    Fila *usuarios_lances = NULL;
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
            int erro = 0;
            cadastrar_produto(produtos, &erro);
            if (erro == 1)
            {
                printf("Erro de alocação de memória\n");
                exit(1);
            }
        }
        else if (opcao == 2)
        {
            // listar_produtos();
        }
        else if (opcao == 3)
        {
            // dar_lance();
        }
        else if (opcao == 4)
        {
            // listar_outros_produtos();
        }
        else if (opcao == 5)
        {
            // remover_produto();
        }
        else if (opcao == 6)
        {
            // encerrar_leilao();
        }
        else
        {
            printf("Opcao invalida! Digite uma das opcoes disponiveis\n");
        }
    }

    return 0;
}