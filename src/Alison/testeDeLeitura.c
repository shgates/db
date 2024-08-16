#include<stdio.h>
#include <stdlib.h>
#include <string.h>


int main (){

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- NESTE PONTO =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

char nome_Tabela[100];
int i = 0;

printf("DIGITE O NOME DA TABELA:\n");
    fgets(nome_Tabela,99,stdin);
    nome_Tabela[strcspn(nome_Tabela, "\n")] = '\0'; // Remove o caractere de nova linha


char nome_arquivo[100]; // Array para armazenar o nome do arquivo completo
    // Cria o nome do arquivo dinamicamente
    sprintf(nome_arquivo, "%s.txt", nome_Tabela);    

    char matrizDeRetorno[70];

    FILE *arquivoREC = fopen(nome_arquivo, "r");

    printf("Iniciando Processo de Leitura do arquivo\n");


    for (i=0;i<70;i++){
      fscanf(arquivoREC,"%c",matrizDeRetorno[i]);
      printf("Caractere lido: %c",matrizDeRetorno[i]);

      if(matrizDeRetorno[i] == '*'){
        if(matrizDeRetorno[i-1] =='&'){
            break;}}

    }

    printf("Iniciando Processo de Leitura da Matriz\n");


     for (i = 0; i < sizeof(matrizDeRetorno) && matrizDeRetorno[i] != '\0'; i++) {
        printf("%c", matrizDeRetorno[i]);
    }
    

    return 0;
}
