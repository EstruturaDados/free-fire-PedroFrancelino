#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ITENS 10

typedef struct {
  char nome[30];
  char tipo[20];
  int quantidade;
} Item;

struct No {
  Item dados;
  struct No* proximo;
};

int totalItems = 0;
struct No *primeiro = NULL;
int resOpt;

void adicionarItem(struct No **inicio) {
    if (totalItems >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    struct No *novo = (struct No*)malloc(sizeof(struct No));

    printf("--- Adicionar Novo Item --- \n");
    printf("Nome do Item: ");
    scanf("%s", novo->dados.nome);
    printf("Tipo do Item (arma, municao, cura, etc...): ");
    scanf("%s", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *inicio;
    *inicio = novo;
    totalItems++;

    printf("Item '%s' adicionado com sucesso!\n", novo->dados.nome);
}

void removerItem(struct No **inicio) {
    if (*inicio == NULL) {
        printf("A mochila já está vazia. Nada a remover\n");
        return;
    }

    char itemRemovido[30];
    printf("--- Remover Item --- \n");
    printf("Digite o nome do item a ser removido: ");
    scanf("%s", itemRemovido);

    struct No *atual = *inicio, *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, itemRemovido) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item '%s' não encontrado na mochila.\n", itemRemovido);
        return;
    }

    if (anterior == NULL) {
        *inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    totalItems--;
    printf("Item '%s' removido com sucesso!\n", itemRemovido);
}
void ordenarPorNome(struct No *inicio) {
    if (inicio == NULL) return;

    struct No *i, *j;
    for (i = inicio; i != NULL; i = i->proximo) {
        for (j = i->proximo; j != NULL; j = j->proximo) {
            if (strcmp(i->dados.nome, j->dados.nome) > 0) {
                Item temp = i->dados;
                i->dados = j->dados;
                j->dados = temp;
            }
        }
    }
    printf("Mochila ordenada por nome!\n");
}
void listarItens(struct No *inicio) {
    if (inicio == NULL) {
        printf("A mochila está vazia\n");
        return;
    }

    printf("--- ITENS NA MOCHILA (%d/%d) --- \n", totalItems, MAX_ITENS);
    printf("NOME            | TIPO            | QUANTIDADE\n");
    printf("---------------------------------------------\n");

    struct No *atual = inicio;
    while (atual != NULL) {
        printf("%-15s | %-15s | %d\n",
           atual->dados.nome,
           atual->dados.tipo,
           atual->dados.quantidade);
        atual = atual->proximo;
    }
}
void buscarItem(struct No *inicio){
    if(inicio == NULL){
      printf("A mochila está vazia!\n");
      return;
    }
    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nomeBusca);

    struct No *atual = inicio;
    while (atual!=NULL)
    {
      if(strcmp(atual->dados.nome,nomeBusca) == 0){
        printf("Item encontrado!\n");
        printf("Nome %s | Tipo: %s | Quantidade: %d", 
        atual->dados.nome,
        atual->dados.tipo,
        atual->dados.quantidade);
        return;
      }
      atual = atual->proximo;
    }
        printf("Item '%s' não encontrado na mochila.\n", nomeBusca);

}
int menu() {
  printf("\n===========================\n");
  printf("   MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA\n");
  printf("===========================\n");
  printf("Itens na Mochila: %d/%d\n", totalItems, MAX_ITENS);

  printf("1. Adicionar Item (Loot)\n");
  printf("2. Remover Item\n");
  printf("3. Listar Itens na Mochila\n");
  printf("4. Buscar Item\n");
  printf("0. Sair\n");
  printf("--------------------------\n");
  printf("Escolha uma opção: ");
  scanf("%d", &resOpt);
  return resOpt;
}

int main() {
  menu();

  while (resOpt != 0) {
    switch (resOpt) {
      case 1:
        adicionarItem(&primeiro);
        break;
      case 2:
        removerItem(&primeiro);
        break;
      case 3:
        ordenarPorNome(primeiro);
        listarItens(primeiro);
        break;
      case 4: 
        buscarItem(primeiro);
        break;
      default:
        printf("Opção inválida!\n");
        break;
    }
    printf("--------------------------------------------------\n");
    printf("Pressione Enter para continuar...\n");
    getchar();
    getchar();
    menu();
  }
  printf("saindo...\n");

  return 0;
}