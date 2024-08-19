#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/*=-=-=-=-=-=-=-=-=-= Leia as pontuações nas seguntes linhas =-=-=-=-=-=-=-=-=-= */

// 97 -98 

// Retorna uma String com o diretorio onde o arquivo a ser lido está
char caminho (char* nome_Tabela){
    char caminhoTabela[1024];
    snprintf(caminhoTabela, sizeof(caminhoTabela), "./%s.txt",nome_Tabela);

    return caminhoTabela;
}



// =-=-=-=-=-=-=-=-=-=-=--==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//
// =-=-=-=-=-=-=-=-=-=-=--==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-//



int rowVerify (char* row, int nCaracteres, char* PrimaryKey) {

    /*
    a) Row: Vetor de caracteres a ser lido.
    b) nCaracteres: Nescessário para a precisão do loop
    c) PrimaryKey: Para comparar se os caracteres da chave são correspondentes
    */

    int i,a;

    // Tamanho de caracteres que a chave primaria abarca.
    int keySize = sizeof(PrimaryKey) / sizeof(PrimaryKey[0]); 

    char *matriz_clone = malloc(sizeof(char) * nCaracteres); // Reservando Vetor

    // Verificação de alocação bem-sucedida
    if (matriz_clone == NULL) {
        return -1;}

    static int confirm = 0;
    int exit = 0;

     for (i=0;i<nCaracteres;i++){

        //Mecnismo para quebra após ler '|'
        if (exit == 1){break;}
        
        
        if (row[i] == '\0') {
           matriz_clone[i] = '\0';} // Marca o final da string caso não consiga ler mais caracteres; 
        else {
         matriz_clone[i] = row[i];} 

        if (matriz_clone[i] == '|'){
            exit++;
            for (a = 0;a<keySize;a++){

                // Em "PrimaryKey[keySize - 1 - a]" o '-1' é nescessario para ajustar indices
                if ((i-1) - a >= 0 && matriz_clone[(i-1)-a] == PrimaryKey[keySize - 1 - a]){confirm++;}
                else{break;}   
             }
            }
            
           }
           free(matriz_clone); // Liberando a memória alocada
           return confirm;
           }



char* delete_Row(char* nome_Tabela, char* PrimaryKey, int nCaracteres, int nRows) {


    int row,column;

    int x;

    char chave_primaria_char[10];
    int keySize = sizeof(PrimaryKey) / sizeof(PrimaryKey[0]);

   
    /* Abrindo arquivo */
    char caminho_Tabela = caminho(nome_Tabela); // Definindo caminho da tabela
    FILE *arquivoInfo = fopen(caminho_Tabela, "r");
    if (arquivoInfo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;}

   
    char *matriz_clone = malloc(sizeof(char)* nCaracteres); // Reservando Vetor.

    /* OBS: Para ler a quantidade de caracteres de uma linha, antes disso é nescessario um vetor de tamanho 'n' onde
    n é a propria quantidade de caracteres */
    
    char **matriz_retorno = malloc(nRows * sizeof(char*)); // Reservando linhas, essa em questão será devolvida.
    for (x=0;x<nRows;x++){// Reservando Colunas, essa em questão será devolvida.
        matriz_retorno[x] = malloc(nCaracteres * sizeof(char));}


    int parmetro_01 = sizeof(PrimaryKey) / sizeof(PrimaryKey[0]);

    while (fgets(matriz_clone, (nCaracteres+1), arquivoInfo)) {
        int i = 0;
        int j = 0;

        int parametro_02 = rowVerify(matriz_clone,nCaracteres,PrimaryKey);
        if (parmetro_01 != parametro_02){
            matriz_retorno[i] = matriz_clone;
            i++;
            j++;

        }
       }

    return matriz_retorno;}

/*
matriz[i][j]

Chave| int A | char B | float C

99|    4      PIPOCA    1.4175
98|    4      PIPOCA    1.4175
97|    4      PIPOCA    1.4175

*/

