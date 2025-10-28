#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Itens da mochila
typedef struct Item {
    char nome[30];        // Nome dos itens
    char tipo[20];        // categoria do item
    int quantidade;       // Quantidade do item
    struct Item* proximo; 
} Item;

// Funcionalidades 
Item* inserirItem(Item* inicio);
Item* removerItem(Item* inicio);
void listarItens(Item* inicio);
void buscarItem(Item* inicio);

int main() {
    Item* mochila = NULL;  // início da lista
    int opcao = -1;

    printf("===== SISTEMA DE INVENTARIO - MOCHILA =====\n");

    while (opcao != 0) {
        printf("\nMenu:\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        if (opcao == 1) {
            mochila = inserirItem(mochila);
        } else if (opcao == 2) {
            mochila = removerItem(mochila);
        } else if (opcao == 3) {
            listarItens(mochila);
        } else if (opcao == 4) {
            buscarItem(mochila);
        } else if (opcao == 0) {
            printf("Encerrando o sistema...\n");
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }
    }

    // Liberar memória antes de sair
    while (mochila != NULL) {
        Item* temp = mochila;
        mochila = mochila->proximo;
        free(temp);
    }

    return 0;
}

// Inserir item 
Item* inserirItem(Item* inicio) {
    Item* novo = (Item*) calloc(1, sizeof(Item));
    if (novo == NULL) {
        printf("Erro: falha ao alocar memoria.\n");
        return inicio;
    }

    printf("Digite o nome do item: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("Digite o tipo do item (arma, municao, cura, ferramenta): ");
    fgets(novo->tipo, sizeof(novo->tipo), stdin);
    novo->tipo[strcspn(novo->tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo->quantidade);
    getchar();

    // Insere no início da lista
    novo->proximo = inicio;
    inicio = novo;

    printf("Item adicionado com sucesso!\n");
    listarItens(inicio);

    return inicio;
}

// Remover item 
Item* removerItem(Item* inicio) {
    if (inicio == NULL) {
        printf("A mochila esta vazia! Nada para remover.\n");
        return inicio;
    }

    char nome[30];
    printf("Digite o nome do item que deseja remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    Item* atual = inicio;
    Item* anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item não achado.\n");
        return inicio;
    }

    if (anterior == NULL) { // remover o primeiro
        inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Item removido com sucesso\n");
    listarItens(inicio);

    return inicio;
}

// Listar itens
void listarItens(Item* inicio) {
    if (inicio == NULL) {
        printf("Mochila mais vazia que a minha conta bancaria\n");
        return;
    }

    printf("\n--- Itens ---\n");
    Item* atual = inicio;
    while (atual != NULL) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               atual->nome, atual->tipo, atual->quantidade);
        atual = atual->proximo;
    }
    printf("-------------------------\n");
}

// Buscar item pelo nome
void buscarItem(Item* inicio) {
    if (inicio == NULL) {
        printf("Mochila vazia.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item que tu procuras: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    Item* atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Item achado\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   atual->nome, atual->tipo, atual->quantidade);
            return;
        }
        atual = atual->proximo;
    }

    printf("Item nao encontrado na mochila.\n");
}