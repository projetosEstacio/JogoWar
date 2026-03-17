#include <stdio.h>
#include <string.h>

// Criação da struct para armazenar os dados do território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {

    // Criacão do Vetor para guardar os cinco territórios
    struct Territorio territorios[5];
    
    printf("============================================================\n");
	printf(" *** CADASTRANDO OS 5 TERRITORIOS DO WAR ***\n");
	printf("============================================================\n");
	
    // laço para cadastrar os 5 territórios
    for(int i = 0; i < 5; i++) {
    	
		
        printf("\n  --- Cadastrando territorio %d --- \n", i + 1);
		printf("-----------------------------------------------------------\n");
        printf(" Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome); 

		printf("\n Digite a cor da tropa ");
		printf("exemplo (azul, vermelho, verde...: ");
        scanf("%s", territorios[i].cor);

        printf("\n Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
       
    }

    // teste de curiosidade
    //printf("\nTecle enter para ver os territorios cadastrados");
    //getchar();
    //getchar();
    
    // Exibindo os territórios cadastrados 
    printf("\n--- Territorios cadastrados ---\n");
    
	// laço para listar os 5 territórios 
    for(int i = 0; i < 5; i++) {
        printf("\n Territorio %d\n", i + 1);
        printf(" Nome: %s\n", territorios[i].nome);
        printf(" Cor do exercito: %s\n", territorios[i].cor);
        printf(" Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0; // término do programa sem erros
}