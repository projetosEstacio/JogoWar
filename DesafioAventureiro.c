#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//================ DEFININDO A STRUCT TERRITÓRIO ===================
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

//================ FUNÇÃO PARA LIMPAR BUFFER =======================
void limparBuffer() {
	int c;		
    while (c = getchar() != '\n' && c != EOF);
}

//================ CADASTRANDO TERRITÓRIOS =========================
void cadastrar(struct Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();

        // Remove o ENTER do fgets
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
    }
}

//================ LISTANDO TERRITÓRIOS ==============================
void listar(struct Territorio* mapa, int total) {
    printf("\n===== LISTA DE TERRITORIOS =====\n");

    for (int i = 0; i < total; i++) {
        printf("\n[%d] Nome: %s\n", i, mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

//================ FUNÇÃO PARA ATACAR =================================
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    
    // Simula valores de  (1 a 6)
    int dadoAtk = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\n=== BATALHA ===\n");
    printf("Atacante (%s) tirou: %d\n", atacante->nome, dadoAtk);
    printf("Defensor (%s) tirou: %d\n", defensor->nome, dadoDef);

    if (dadoAtk > dadoDef) {
        printf("\nO atacante (%s) venceu a batalha!\n", atacante->nome);

        // Transfere metade das tropas
        int tropasTransferidas = atacante->tropas / 2;

        defensor->tropas = tropasTransferidas;

        // Atualiza a cor (mudou de dono)
        strcpy(defensor->cor, atacante->cor);

        // Remove tropas do atacante
        atacante->tropas -= tropasTransferidas;

    } else {
        printf("\nO Defensor (%s) venceu a batalha!\n", defensor->nome);

        // Atacante perde 1 tropa
        atacante->tropas--;

        if (atacante->tropas < 0)
            atacante->tropas = 0;
    }
}

//================ LIBERANDO MEMÓRIA =================================
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}

//================ MAIN ==================
int main() {

    int total;
    int opcao;
    int atk, def;

    // Inicializa aleatoriedade
    srand(time(NULL));

    printf("Quantos territorios deseja criar? ");
    scanf("%d", &total);
    limparBuffer();

    // ALOCAÇÃO DINÂMICA
    struct Territorio* mapa = (struct Territorio*) calloc(total, sizeof(struct Territorio));
    // verificando se há erro ao alocar memória
    if (mapa == NULL) {
    	printf("Erro ao alocar memoria\n");
    	return 1;
	}

    // Cadastro inicial
    cadastrar(mapa, total);

    // MENU
    do {
        printf("\n=============================\n");
        printf("1 - Listar territorios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("===============================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {

            case 1:
                listar(mapa, total);
                break;

            case 2:
                listar(mapa, total);

                printf("\nEscolha o indice do ATACANTE: ");
                scanf("%d", &atk);

                printf("Escolha o indice do DEFENSOR: ");
                scanf("%d", &def);
                limparBuffer();

                // Validação
                if (atk == def) {
                    printf("Nao pode atacar o mesmo territorio!\n");
                } 
                else if (strcmp(mapa[atk].cor, mapa[def].cor) == 0) {
                    printf("Nao pode atacar territorio da mesma cor!\n");
                } 
                else {
                    atacar(&mapa[atk], &mapa[def]);
                }

                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    // Libera memória
    liberarMemoria(mapa);

    return 0;
}