#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
//funcao cadastrar produto
void cadastrar_produto()

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


int main () {
    int opcao = 0;
    while (opcao != 6)
    {
        printf("Caro usuário, suas opcoes sao:\n");
        printf("1) Cadastrar um produto\n");
        printf("2) listar produtos e lances\n");
        printf("3) dar um lance\n");
        printf("4) listar outros produtos disponiveis\n");
        printf("5) remover produto\n");
        printf("6) encerrar leilao\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            //cadastrar_produto();
        }
        else if (opcao == 2)
        {
            //listar_produtos();
        }
        else if (opcao == 3)
        {
            //dar_lance();
        }
        else if (opcao == 4)
        {
            //listar_outros_produtos();
        }
        else if (opcao == 5)
        {
            //remover_produto();
        }
        else if (opcao == 6)
        {
            //encerrar_leilao();
        }
        else
        {
            printf("Opcao invalida\n");
        }
        
    }
    return 0;

}