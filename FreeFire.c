#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// --- Struct Item ---
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int prioridade; // 1 (menor) a 5 (maior)
} Item;

// --- Enum para critérios de ordenação ---
typedef enum {
    NOME,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;

// --- Variáveis globais ---
Item mochila[MAX_ITENS];
int numItens = 0;
bool ordenadaPorNome = false;

// --- Protótipos ---
void limparTela();
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void menuDeOrdenacao();
void insertionSort(CriterioOrdenacao criterio);
void buscaBinariaPorNome();

int main() {
    int opcao;
    do {
        limparTela();
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch(opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("Saindo do jogo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
        if(opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    } while(opcao != 0);

    return 0;
}

// --- Funções ---
void limparTela() {
    for(int i = 0; i < 30; i++) printf("\n");
}

void exibirMenu() {
    printf("=== Desafio Código da Ilha – Free Fire ===\n");
    printf("Itens na mochila: %d | Ordenada por nome: %s\n", numItens, ordenadaPorNome ? "SIM" : "NAO");
    printf("-----------------------------------------\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar itens\n");
    printf("5. Buscar item por nome\n");
    printf("0. Sair\n");
    printf("-----------------------------------------\n");
}

void inserirItem() {
    if(numItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }
    getchar(); // limpar buffer
    printf("Nome do item: ");
    fgets(mochila[numItens].nome, MAX_NOME, stdin);
    mochila[numItens].nome[strcspn(mochila[numItens].nome, "\n")] = '\0';

    printf("Tipo do item (arma, municao, cura, ferramenta): ");
    fgets(mochila[numItens].tipo, MAX_TIPO, stdin);
    mochila[numItens].tipo[strcspn(mochila[numItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[numItens].quantidade);
    printf("Prioridade (1 a 5): ");
    scanf("%d", &mochila[numItens].prioridade);

    numItens++;
    ordenadaPorNome = false;
    printf("Item adicionado com sucesso!\n");
}

void removerItem() {
    if(numItens == 0) {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }
    getchar(); // limpar buffer
    char nome[MAX_NOME];
    printf("Digite o nome do item a remover: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for(int i = 0; i < numItens; i++) {
        if(strcmp(mochila[i].nome, nome) == 0) {
            for(int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

void listarItens() {
    if(numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    printf("\n--- Itens na Mochila ---\n");
    printf("NOME\tTIPO\tQUANTIDADE\tPRIORIDADE\n");
    printf("--------------------------------------------\n");
    for(int i = 0; i < numItens; i++) {
        printf("%s\t%s\t%d\t\t%d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

void menuDeOrdenacao() {
    if(numItens <= 1) {
        printf("Itens insuficientes para ordenar.\n");
        return;
    }
    int opc;
    printf("Escolha o criterio de ordenacao:\n");
    printf("1. Nome\n2. Tipo\n3. Prioridade\nOpcao: ");
    scanf("%d", &opc);
    if(opc < 1 || opc > 3) {
        printf("Opcao invalida.\n");
        return;
    }
    insertionSort(opc - 1);
}

void insertionSort(CriterioOrdenacao criterio) {
    int comparacoes = 0;
    for(int i = 1; i < numItens; i++) {
        Item key = mochila[i];
        int j = i - 1;

        while(j >= 0) {
            bool cond = false;
            comparacoes++;
            if(criterio == NOME && strcmp(mochila[j].nome, key.nome) > 0) cond = true;
            else if(criterio == TIPO && strcmp(mochila[j].tipo, key.tipo) > 0) cond = true;
            else if(criterio == PRIORIDADE && mochila[j].prioridade < key.prioridade) cond = true;

            if(!cond) break;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = key;
    }
    if(criterio == NOME) ordenadaPorNome = true;
    else ordenadaPorNome = false;
    printf("Itens ordenados com sucesso! Comparacoes realizadas: %d\n", comparacoes);
}

void buscaBinariaPorNome() {
    if(!ordenadaPorNome) {
        printf("A mochila deve estar ordenada por NOME para realizar a busca binaria.\n");
        return;
    }
    if(numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    getchar(); // limpar buffer
    char alvo[MAX_NOME];
    printf("Digite o nome do item a buscar: ");
    fgets(alvo, MAX_NOME, stdin);
    alvo[strcspn(alvo, "\n")] = '\0';

    int left = 0, right = numItens - 1, comparacoes = 0;
    while(left <= right) {
        int mid = (left + right) / 2;
        comparacoes++;
        int cmp = strcmp(mochila[mid].nome, alvo);
        if(cmp == 0) {
            printf("Item encontrado apos %d comparacoes!\n", comparacoes);
            printf("Nome: %s | Tipo: %s | Quantidade: %d | Prioridade: %d\n",
                   mochila[mid].nome,
                   mochila[mid].tipo,
                   mochila[mid].quantidade,
                   mochila[mid].prioridade);
            return;
        } else if(cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("Item nao encontrado apos %d comparacoes.\n", comparacoes);
}
