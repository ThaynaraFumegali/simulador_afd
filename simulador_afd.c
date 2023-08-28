/**
 * Código base disponível em https://github.com/jbelgamazzi/simulador_afd.
 * Personalizado por Thaynara Fumegali - Acadêmica do Curso de Ciência da Computação
 * Descrição
 * Este programa é um simulador de Autômatrizos Finitos Deterministicos (A.F.D)
 * por meio de leitura de arquivouivos (txt).
 *
 */

/**
 * Descrição do arquivouivo (txt) complementar
 *
 * O arquivouivo (txt) será responsavél por fornecer os dados nescesários para realizar
 * a simulação de um autômatrizo, para isso o arquivouivo (txt) deve ser escrito conforme o
 * exemplo abaixo:
 *
 * EXEMPLO: Deve-se escrever o arquivouivo da seguinte forma: (sem os comentários em parenteses)
 *
 * 0      - estadoInicial
 * ab     (alfabeto)
 * 4      (nº de estados)
 * 1      (nº de estados finais)
 * 3      (estado estadoFinal. Caso haja mais de um deve ser informado na sequancia, uma abaixo do outro)
 * 0 a 1  (TRANSIÇÃO: Q0 com 'a' vai para Q1)
 * 0 b 2  (TRANSIÇÃO: Q0 com 'b' vai para Q1)
 * 1 a 3  (TRANSIÇÃO: Q1 com 'a' vai para Q3)
 * 1 b 2  (TRANSIÇÃO: Q1 com 'b' vai para Q2)
 * 2 a 1  (TRANSIÇÃO: Q2 com 'a' vai para Q1)
 * 2 b 3  (TRANSIÇÃO: Q2 com 'b' vai para Q3)
 * 3 a 3  (TRANSIÇÃO: Q3 com 'a' vai para Q3)
 * 3 b 3  (TRANSIÇÃO: Q3 com 'b' vai para Q3)
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void openFile(int ***matrizTransicao,int **estadoFinal,int *nEstados,int *estadoInicial,int *nEstadosFinais){

    FILE *arquivo    = NULL;
    int  **transicao = NULL;
    int	  *finais    = NULL;
    int  i, j, k, x, fim;
    char y;
    char arqName[50];
    char alfabeto[50];

    printf("\n\n\nDigite o nome do arquivouivo (com .txt nmo final) com a transicao: \n");
    gets(arqName);

    arquivo = fopen(arqName,"r");

    if(arquivo == NULL){
        printf("\n\nERROR: Nao foi possivel ler o arquivouivo"
               "\n\nVerifique se o nome e/ou caminho estao corretos"
               "\nA extensao do arquivo deve ser .txt\n\n");
        system("Pause");
        exit(1);
    }

    // Pega informações
    fscanf(arquivo, "%i", estadoInicial);
    fscanf(arquivo, "%s", alfabeto);
    fscanf(arquivo, "%i", nEstados);
    fscanf(arquivo, "%i", nEstadosFinais);

    //Imprime informações
    printf("\nEstado Inicial:            Q%i" , *estadoInicial);
    printf("\nAlfabeto:                  %s"  , alfabeto);
    printf("\nNumero de Estados:         %i"  , *nEstados);
    printf("\nNumero de Estados Finiais: %i\n", *nEstadosFinais);

    //\_ Aloca a transição em uma matrizriz
    transicao = (int **)malloc((*nEstados)*sizeof(int *));

    if(transicao == NULL){
        printf("\n\nERROR: Nao foi possivel alocar a transicao na matrizriz\n");
        system("Pause");
        exit(1);
    }

    for(i=0; i<(*nEstados); i++){
        transicao[i] = (int *)malloc(strlen(alfabeto)*sizeof(int));
        if(transicao[i] == NULL)
        exit(1);
    }

    //\_ Aloca o conjunto de estados finais (vetor)
    finais = (int *)malloc((*nEstadosFinais)*sizeof(int));

    if(finais == NULL){
        printf("\n\nERROR: Nao foi possivel alocar o vetor de estados finais\n");
        system("Pause");
        exit(1);
    }

    for(k=0; k<(*nEstadosFinais); k++){
        fscanf(arquivo, "%i", &fim);
        finais[fim] = fim;
        //\_ Printa na tela quem sao os estados finais
        printf("\nEstado Final = Q%i\t", finais[fim]);
    }

    //\_ Printa na tela a transição do A.F.D
    printf("\n\nFuncao de Transicao do A.F.D\n\n");
	
    printf("-------------------------\n");

    for(i=0; i<(*nEstados); i++){
	for(j=0; j<strlen(alfabeto); j++){
		fscanf(arquivo, "%i %c %i", &x, &y, &transicao[i][j]);
		printf("|  Q%i  |   %c   |   Q%i   |\n", x, y, transicao[i][j]);
		printf("-------------------------\n");
	}
    }

    (*matrizTransicao) = transicao;
    (*estadoFinal)  = finais;
    
    fclose(arquivo);
}

void validaPalavra(int ***matrizTransicao,int **estadoFinal,int *estadoInicial,char simbolo[50]){
    int i,estado;
    int **transicao = NULL;
    int  *finais    = NULL;

    transicao = *matrizTransicao;
    finais    = *estadoFinal;
    estado    = (*estadoInicial);
    i = 0;

    while(i < strlen(simbolo)){
        estado = transicao[estado][simbolo[i] - 'a'];
        printf("\n\n %c -> Q%i\n", simbolo[i], estado);
        i++;
    }

    if(finais[estado] == estado){
	printf("\n\n\nPalavra ( %s ) foi ACEITA! O estado parada foi: Q%i\n\n\n", simbolo, estado);
    }else{
	printf("\n\n\nPalavra ( %s ) foi REJEITADA! O estado de parada foi: Q%i\n\n\n", simbolo, estado);
    }
}

int main(){

    int **transicao = NULL;
    int	 *finais    = NULL;
    int  i,j,k;
    int  estadoInicial;
    int  nEstados;
    int  nEstadosFinais;
    char simbolo[50],op;

    //\_ Define o titulo da janela do simulador
    system("title Simulador de Autômatrizos Finitos Desterministicos (A.F.D)");

    do{
	//\_ Limpar o buffer (no windows) (no Linux: __fpurge(stdin) );
        fflush(stdin);
        //\_ Limpar a tela
        system("cls");

        printf("\n\t| ********************************************************** |"
               "\n\t|   SIMULADOR DE AUTOMATOS FINITOS DETERMINISTICOS (A.F.D)   |"
               "\n\t| ********************************************************** |");

	openFile(&transicao,&finais,&nEstados,&estadoInicial,&nEstadosFinais);

	//\_ Limpar o buffer (no windows) (no Linux: __fpurge(stdin) );
        fflush(stdin);

	printf("\nDigite a palavra qual deseja validar: ");
	//\_ Limpar o buffer (no windows) (no Linux: __fpurge(stdin) );
        fflush(stdin);
	scanf("%s",simbolo);

	validaPalavra(&transicao,&finais,&estadoInicial,simbolo);

	//Laço para liberar a matrizriz
        for(i=(nEstados-1); i>=0; i--){
            free(transicao[i]);
        }
        
        free(transicao);
        free(finais);
        
        printf("\n\nDeseja abrir outro arquivouivo de transicao - (S/N)?");
        scanf("%s", &op);

	}while(op == 'S' || op == 's');
	
	system("Pause");
}
