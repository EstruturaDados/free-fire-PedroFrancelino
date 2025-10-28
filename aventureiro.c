#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

void inserirItemVetor(Item* vetor, int* tamanho) {
    if (*tamanho >= 100) return;
    printf("Nome: ");
    fgets(vetor[*tamanho].nome, 30, stdin);
    vetor[*tamanho].nome[strcspn(vetor[*tamanho].nome, "\n")] = 0;
    printf("Tipo: ");
    fgets(vetor[*tamanho].tipo, 20, stdin);
    vetor[*tamanho].tipo[strcspn(vetor[*tamanho].tipo, "\n")] = 0;
    printf("Quantidade: ");
    scanf("%d", &vetor[*tamanho].quantidade);
    getchar();
    (*tamanho)++;
}

void listarItensVetor(Item* vetor, int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++)
        printf("%d - %s | %s | %d\n", i + 1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
}

int buscarSequencialVetor(Item* vetor, int tamanho, char* nome) {
    comparacoesSequencial = 0;
    int i;
    for (i = 0; i < tamanho; i++) {
        comparacoesSequencial++;
        if (strcmp(vetor[i].nome, nome) == 0) return i;
    }
    return -1;
}

void removerItemVetor(Item* vetor, int* tamanho, char* nome) {
    int pos = buscarSequencialVetor(vetor, *tamanho, nome);
    if (pos == -1) return;
    int i;
    for (i = pos; i < *tamanho - 1; i++) vetor[i] = vetor[i + 1];
    (*tamanho)--;
}

void ordenarVetor(Item* vetor, int tamanho) {
    int i, j;
    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - 1 - i; j++) {
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Item temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

int buscarBinariaVetor(Item* vetor, int tamanho, char* nome) {
    comparacoesBinaria = 0;
    int inicio = 0, fim = tamanho - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(vetor[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void inserirItemLista(No** inicio) {
    No* novo = (No*) malloc(sizeof(No));
    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = 0;
    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = 0;
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();
    novo->proximo = *inicio;
    *inicio = novo;
}

void listarItensLista(No* inicio) {
    No* atual = inicio;
    int i = 1;
    while (atual != NULL) {
        printf("%d - %s | %s | %d\n", i, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
        i++;
    }
}

int buscarSequencialLista(No* inicio, char* nome) {
    comparacoesSequencial = 0;
    No* atual = inicio;
    int pos = 0;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) return pos;
        atual = atual->proximo;
        pos++;
    }
    return -1;
}

void removerItemLista(No** inicio, char* nome) {
    No* atual = *inicio;
    No* anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) *inicio = atual->proximo;
            else anterior->proximo = atual->proximo;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

int main() {
    Item vetor[100];
    int tamanho = 0;
    No* lista = NULL;
    int opcaoPrincipal = 1;
    while (opcaoPrincipal != 0) {
        printf("\n1 - Mochila com vetor\n2 - Mochila com lista encadeada\n0 - Sair\nEscolha: ");
        scanf("%d", &opcaoPrincipal);
        getchar();
        if (opcaoPrincipal == 1) {
            int opcaoVetor = 1;
            while (opcaoVetor != 0) {
                printf("\n1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar sequencial\n5 - Ordenar\n6 - Buscar binaria\n0 - Voltar\nEscolha: ");
                scanf("%d", &opcaoVetor);
                getchar();
                if (opcaoVetor == 1) inserirItemVetor(vetor, &tamanho);
                else if (opcaoVetor == 2) {
                    char nome[30];
                    printf("Nome para remover: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    removerItemVetor(vetor, &tamanho, nome);
                } else if (opcaoVetor == 3) listarItensVetor(vetor, tamanho);
                else if (opcaoVetor == 4) {
                    char nome[30];
                    printf("Nome para buscar: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    int pos = buscarSequencialVetor(vetor, tamanho, nome);
                    if (pos >= 0) printf("Encontrado na posicao %d\n", pos);
                    else printf("Nao encontrado\n");
                    printf("Comparacoes sequencial: %d\n", comparacoesSequencial);
                } else if (opcaoVetor == 5) ordenarVetor(vetor, tamanho);
                else if (opcaoVetor == 6) {
                    char nome[30];
                    printf("Nome para busca binaria: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    int pos = buscarBinariaVetor(vetor, tamanho, nome);
                    if (pos >= 0) printf("Encontrado na posicao %d\n", pos);
                    else printf("Nao encontrado\n");
                    printf("Comparacoes binaria: %d\n", comparacoesBinaria);
                }
            }
        } else if (opcaoPrincipal == 2) {
            int opcaoLista = 1;
            while (opcaoLista != 0) {
                printf("\n1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar sequencial\n0 - Voltar\nEscolha: ");
                scanf("%d", &opcaoLista);
                getchar();
                if (opcaoLista == 1) inserirItemLista(&lista);
                else if (opcaoLista == 2) {
                    char nome[30];
                    printf("Nome para remover: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    removerItemLista(&lista, nome);
                } else if (opcaoLista == 3) listarItensLista(lista);
                else if (opcaoLista == 4) {
                    char nome[30];
                    printf("Nome para buscar: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    int pos = buscarSequencialLista(lista, nome);
                    if (pos >= 0) printf("Encontrado na posicao %d\n", pos);
                    else printf("Nao encontrado\n");
                    printf("Comparacoes sequencial: %d\n", comparacoesSequencial);
                }
            }
        }
    }
    return 0;
}