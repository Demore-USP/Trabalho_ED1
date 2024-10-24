#ifndef LISTA_H
#define LISTA_H

#include "pilha.h"
#include "fila.h"
#include "lista_simples.h"

// Criando a struct que armazena os produtos
// junto com os usuários e seus respectivos lances
typedef struct no_lista
{
    char *produto;
    Fila usuarios;
    Pilha lances;
    struct no_lista *prox;
} No_Lista;

// Ponteiros de início e fim da lista de produtos
typedef struct Lista
{
    No_Lista *ini;
    No_Lista *fim;
} Lista;

void inicializar_lista(Lista *);
int lista_vazia(Lista *);
void inserir_produto_lista(Lista *, char *, int *);
No_Lista *procurar_produto(Lista *, char *, int *);
int esta_na_lista(Lista *, char *, int *);
void remover_da_lista(Lista *, char *, int *);
void imprimir_produtos(Lista *, int *);
void excluir_lista(Lista *, int *);
void inserir_lance(Lista *, char *, float, char *, int *);
char *buscar_produto_especifico(Lista *, int, int *);
char *buscar_usuario_ganhador(Lista *, int, int *);
float buscar_maior_lance(Lista *, int, int *);
int numero_de_produtos(Lista *, int *);
int buscar_indice_produto(Lista *, char *, int *);
void encontrar_recomendacoes(Lista *, int *, Lista_simples *);
int numero_usuarios(Lista_simples *, int *);
char *retornar_nome(Lista_simples *, int, int *);
char *recomendar(Lista *, int, char *, int *);
Pilha *pilha_especifica(Lista *, char *, int *);
Fila *fila_especifica(Lista *, char *, int *);

#endif
