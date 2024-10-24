#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "fila.h"
#include "pilha.h"
#include "lista_simples.h"

// Função que cadastra um produto na lista
void cadastrar_produto(Lista *lista_de_produtos, int *erro)
{
    char nome_produto[50];
    printf("Entre com o nome do produto: ");
    scanf("%s", nome_produto);

    inserir_produto_lista(lista_de_produtos, nome_produto, erro);

    if (*erro)
        return; // caso haja algum erro, retorna

    printf("Produto cadastrado com sucesso!\n");
    return;
}

// funcao_listar_produtos_lances  ***Tem que ser chamada junto com a funcao listar lances
void listar_produtos_lances(Lista *lista_de_produtos, int *erro)
{
    if (lista_vazia(lista_de_produtos))
    {
        *erro = 1; // Lista vazia ou não inicializada
        return;
    }

    char *nome_produto;

    for (int i = 0; i < numero_de_produtos(lista_de_produtos, erro); i++)
    {
        nome_produto = buscar_produto_especifico(lista_de_produtos, i, erro); // coleta o nome do produto por seu "índice na lista"
        printf("%s\n", nome_produto);                                         // Imprime o nome do produto

        // Cria e inicializa uma cópia da fila de usuários
        Fila fila_copia;
        inicializar_fila(&fila_copia);
        copiar_fila(fila_especifica(lista_de_produtos, nome_produto, erro), &fila_copia, erro); // copia a fila de usuarios do produto especificado
        if (*erro != 0)
        {
            return; // Retorna se houver erro ao copiar a fila
        }

        fila_copia = inverter_fila(&fila_copia, erro); // inverte a fila para poder opera-la de acordo com a necessidade da impressão

        // Cria e inicializa uma cópia da pilha de lances
        Pilha pilha_copia;
        inicializar_pilha(&pilha_copia);
        copiar_pilha(pilha_especifica(lista_de_produtos, nome_produto, erro), &pilha_copia, erro); // copia a pilha de lances do produto especificado
        if (*erro != 0)
        {
            return; // Retorna se houver erro ao copiar a pilha
        }

        float valor_anterior, valor_atual; // declara um valor anterior e atual para comparação de lances iguais
        char *nome_usuario;                // nome a ser impresso de cada lance
        int contador;                      // contador de lances iguais
        while (!fila_vazia(&fila_copia))
        { // enquanto a fila não esta vazia remove o primeiro da fila e o topo da pilha
            nome_usuario = remover_da_fila(&fila_copia, erro);
            valor_anterior = desempilhar(&pilha_copia, erro);
            if (*erro != 0)
            {
                return; // Retorna se houver erro ao copiar a fila
            }
            if (!pilha_vazia(&pilha_copia)) // se a pilha ainda não estiver vazia remove o proximo dela para comparar com o anterior
                valor_atual = desempilhar(&pilha_copia, erro);
            if (*erro != 0)
                return; // Retorna se houver erro ao desempilhar

            contador = 1; // Reseta o contador de lances consecutivos

            // Verifica se há lances consecutivos iguais
            while (valor_anterior == valor_atual && !pilha_vazia(&pilha_copia))
            {
                contador++; // conta quantos lances são iguais ao compara-los
                valor_atual = desempilhar(&pilha_copia, erro);
                if (*erro != 0)
                {
                    return; // Interrompe se houver erro
                }
            }

            // Imprime lances iguais no caso em que existem
            if (contador > 1)
            {
                printf("%d lances de R$%.2f: ", contador, valor_anterior);
                for (int i = 0; i < contador; i++)
                {
                    if (i < contador - 1)
                    { // esse if then else esta aqui apenas para imprimir em uma formatação específica com virgulas entre os nomes dos usuários
                        printf("%s, ", nome_usuario);
                        nome_usuario = remover_da_fila(&fila_copia, erro); // passa para o próximo da fila que tambem deu um lance igual
                    }
                    else
                    {
                        printf("%s\n", nome_usuario);
                        empilhar(&pilha_copia, valor_atual, erro);
                    }
                    if (*erro != 0)
                        return; // Retorna se houver erro ao remover da fila
                }
            }
            else // se não houverem iguais devolve o lance comparado com o anterior para a pilha para evitar de desempilhar mais do que há de elementos na pilha
            {
                empilhar(&pilha_copia, valor_atual, erro);
                printf("1 lance de R$%.2f: %s\n", valor_anterior, nome_usuario);
            }
            valor_anterior = 0;
            valor_atual = 0;
            // Atualiza valor_anterior e atual para a próxima comparação
        }
    }
    printf("Listagem completa!\n");
    return;
}

// funcao dar lance !!!!!!!!!!!!!!!!Função não testada
void dar_lance(Lista *lista_de_produtos, int *erro)
{
    char nome_usuario[50], nome_produto[50];
    float valor;

    printf("Entre com seu nome: ");
    scanf("%s", nome_usuario);
    printf("\nEntre com o valor do lance: R$ ");
    scanf("%f", &valor);
    printf("\nEntre com o nome do produto: ");
    scanf("%s", nome_produto);
    if (!esta_na_lista(lista_de_produtos, nome_produto, erro))
    {
        printf("Produto não encontrado no leilão. Escolha um produto existente\n");
        return;
    }
    else if (valor < buscar_maior_lance(lista_de_produtos, buscar_indice_produto(lista_de_produtos, nome_produto, erro), erro))
    {
        printf("Seu lance pelo(a) %s não foi aceito. Você precisa dar um lance maior\n", nome_produto);
        return;
    }
    inserir_lance(lista_de_produtos, nome_produto, valor, nome_usuario, erro);

    printf("\nLance dado com sucesso!\n");
    return;
}

// funcao listar outros produtos
void listar_outros_produtos(Lista *lista_de_produtos, int *erro, Lista_simples *usuarios_recomendar)
{
    // Chamada da função para encontrar recomendações
    encontrar_recomendacoes(lista_de_produtos, erro, usuarios_recomendar);

    // Verificar se houve erro na função encontrar_recomendacoes
    if (*erro) {
        printf("Erro ao encontrar recomendações.\n");
        return;  // Interrompe a execução caso ocorra um erro
    }

    // Obtém a quantidade de usuários para recomendar
    int qtd_nomes = numero_usuarios(usuarios_recomendar, erro);
    if (*erro) {
        printf("Erro ao obter o número de usuários para recomendação.\n");
        return;
    }

    // Obtém a quantidade de produtos
    int qtd_produtos = numero_de_produtos(lista_de_produtos, erro);
    if (*erro) {
        printf("Erro ao obter o número de produtos.\n");
        return;
    }

    // Loop pelos usuários recomendados
    for (int i = 0; i < qtd_nomes; i++)
    {
        // Retorna o nome atual da lista de usuários recomendados
        char *nome_atual = retornar_nome(usuarios_recomendar, i, erro);
        if (*erro) {
            printf("Erro ao retornar o nome do usuário na posição %d.\n", i);
            continue;  // Pula para o próximo usuário caso ocorra erro
        }

        // Exibe a recomendação inicial para o usuário
        printf("Para %s: nao gostaria de dar um lance por:\n", nome_atual);

        // Loop pelos produtos e tenta recomendar para o usuário atual
        for (int j = 0; j < qtd_produtos; j++)
        {
            char *produto_recomendado = recomendar(lista_de_produtos, j, nome_atual, erro);

             if (produto_recomendado != NULL && produto_recomendado[0] != '\0') {
                printf("- %s\n", produto_recomendado);
            }
        }
    }
}


// funcao remover produto
void remover_produto(Lista *lista_de_produtos, int *erro)
{

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
void encerrar_leilao(Lista *produtos, int *erro)
{
    int i = 0;
    while (i < numero_de_produtos(produtos, erro))
    {
        printf("%s", buscar_produto_especifico(produtos, i, erro));
        printf(": ");
        if (buscar_usuario_ganhador(produtos, i, erro) == NULL)
        {
            printf("Nenhum lance foi dado para esse produto\n");
            i++;
            continue;
        }
        printf("%s ", buscar_usuario_ganhador(produtos, i, erro));
        printf("comprou por R$");
        printf("%.2f\n", buscar_maior_lance(produtos, i, erro));
        i++;
    }
    printf("Leilão encerrado!\n");
    excluir_lista(produtos, erro);
}

int main()
{

    Lista lista_de_produtos;
    Lista_simples usuarios_recomendar;
    int erro = 0;
    int opcao = 0;

    inicializar_lista(&lista_de_produtos);
    inicializar_lista_simples(&usuarios_recomendar);

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
            switch (erro)
            {
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
            listar_produtos_lances(&lista_de_produtos, &erro);
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

            listar_outros_produtos(&lista_de_produtos, &erro, &usuarios_recomendar);
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