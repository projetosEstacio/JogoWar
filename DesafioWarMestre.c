#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//================ NÚMEROS MÁXIMOS PERMITIDOS NO JOGO =================

#define MAX_TERRITORIOS 5
#define MAX_MISSAO 100

//================ DEFINIÇÃO DE STRUCT ================================

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

//================ PROTÓTIPOS DE FUNÇÕES ==============================

void limparBuffer();
void exibirMenu();
void cadastrar(struct Territorio *mapa, int total);
void imprimirMapa(struct Territorio *mapa, int total);
void atacar(struct Territorio *atk, struct Territorio *def);
void atribuirMissao(char *destino, char *missoes[], int total);
int verificarMissao(char *missao, struct Territorio *mapa, int total);
void liberarMemoria(struct Territorio *mapa, char *missao);

//================ FUNÇÃO PRINCIPAL MAIN ==============================

int main() {

    srand(time(NULL));

    int total, opcao, atk, def;
		
	// ------------Leitura e verificação da quantidade de territórios --- 
	do {
    	printf("Quantidade de territorios (entre 1 e %d): ", MAX_TERRITORIOS);
    	if(scanf("%d", &total) !=1) {
    		printf("Entrada invalida digite um numero valido.\n");
    		while (getchar() != '\n'); // limpa o buffer
    		total = 0; // se a entra foi inválida força o loop a continuar
    	}
    	else if(total < 1 || total > MAX_TERRITORIOS) {
    		printf("Numero invalido! Apenas entre 1 e %d.\n", MAX_TERRITORIOS);
    		while (getchar() != '\n');
		}
		else{
			while (getchar() != '\n');
		}
    	
    } while (total < 1 || total > MAX_TERRITORIOS);
	
	// -------------------- Alocando memória -----------------------------
	
	struct Territorio *mapa = calloc(total, sizeof(struct Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    cadastrar(mapa, total);
    imprimirMapa(mapa, total);
	
	//-------------------- Montando um array de ponteiros p/missões --
	
    char *missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar cor vermelha",
        "Dominar maioria",
        "Conquistar 2 territorios seguidos",
        "Eliminar tropas inimigas"
    };

    char *minhaMissao = malloc(MAX_MISSAO);
    atribuirMissao(minhaMissao, missoes, 5);

    printf("\nSua missao: %s\n", minhaMissao);
	//-------------------------------------------------------------------
    // =================== EXIBIÇÃO DO MENU =============================
    //-------------------------------------------------------------------
    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {

            case 1: // ATACAR

                printf("\nIndice atacante: ");
                scanf("%d", &atk);

                printf("Indice defensor: ");
                scanf("%d", &def);
                limparBuffer();

                if (atk == def) {
                    printf("Territorio invalido!\n");
                }
                else if (strcmp(mapa[atk].cor, mapa[def].cor) == 0) {
                    printf("Mesma cor!\n");
                }
                else {
                    atacar(&mapa[atk], &mapa[def]);
                }
                break;

            case 2: // VERIFICAR MISSÃO

                if (verificarMissao(minhaMissao, mapa, total)) {
                    printf("\n*** MISSAO CUMPRIDA! VOCE VENCEU! ***\n");
                    opcao = 3;
                } else {
                    printf("\nMissao ainda nao concluida.\n");
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa, minhaMissao);

    return 0;
}
    //------------------------------------------------------------------
    // =================== FUNÇÕES FORA DO MAIN ========================
    //-------------------- exibir menu ---------------------------------

void exibirMenu() {
    printf("\n=== MENU ===\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("\nEscolha sua opcao: ");
}
	//-------------------- limpar buffer  ---------------------------------
	
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
    //-------------------- cadastrar território  --------------------------
    
void cadastrar(struct Territorio *mapa, int total) {

    for (int i = 0; i < total; i++) {

        printf("\nTerritorio %d\n", (i));

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);

        printf("Cor: ");
        fgets(mapa[i].cor, 10, stdin);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBuffer();

	//--------------------Cortando o \n da string nome e cor -----------
	
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';
    }
}
	//-------------------- imprimir mapa de territórios  ----------------
	
void imprimirMapa(struct Territorio *mapa, int total) {
	printf("//================ MOSTRANDO O MAPA PARA JOGAR ============\n");
	for (int i = 0; i < total; i++){
		printf("%d. %s (Exercito: %s, Tropas: %d)\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
				
	}
	
}
	//-------------------- função para ataque   ------------------------
	
void atacar(struct Territorio *atk, struct Territorio *def) {

    int dadoAtk = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\nAtaque: %s %d x %s %d\n", atk->nome, dadoAtk, def->nome, dadoDef);

    if (dadoAtk > dadoDef) {

        int metade = atk->tropas / 2;

        def->tropas = metade;
        strcpy(def->cor, atk->cor);

        atk->tropas -= metade;

        printf("\nAtacante %s venceu!\n", atk->nome);
        printf("Defensor %s agora pertence a cor %s e tem %d tropas.\n", def->nome, def->cor, def->tropas);

    } else {
        atk->tropas--;

        if (atk->tropas < 0)
            atk->tropas = 0;

        printf("\nDefensor %s venceu!\n", def->nome);
        printf("Atacante %s agora tem %d tropas.\n", atk->nome, atk->tropas);
    }
}
	//-------------------- Atribuir missões   -------------------------
	
void atribuirMissao(char *destino, char *missoes[], int total) {
    int sorteio = rand() % total;
    strcpy(destino, missoes[sorteio]);
}
   //-------------------- Verificação simples de uma missão cumprida --
   
int verificarMissao(char *missao, struct Territorio *mapa, int total) {

    int cont = 0;

    for (int i = 0; i < total; i++) {
        if (strcmp(mapa[i].cor, mapa[0].cor) == 0)
            cont++;
    }

    if (cont >= 5 && strstr(missao, "5 territorios"))
        return 1;

    return 0;
}
	//-------------------- Liberação de memória   -----------------------
	
	void liberarMemoria(struct Territorio *mapa, char *missao) {
    free(mapa);
    free(missao);
}