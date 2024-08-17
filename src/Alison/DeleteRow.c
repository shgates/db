#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Nescessario passar numero de caracteres

char caminho (char* nome_Tabela){
    char caminhoTabela[1024];
    snprintf(caminhoTabela, sizeof(caminhoTabela), "./%s.txt",nome_Tabela);

    return caminhoTabela;
}

char delete_Row(char* nome_Tabela, char *PrimaryKey, int nCaracteres) {

// Se chavePrimaria for recebida como char temos que isolar cada caractere em uma matriz a parte
// Se chavePrimaria for recebida como inteiro, de qualquer forma temos que comparar caractere por caractere, o que não da pra fazer com interio


    int i,j,a;
    int linha;
    int row,column;

    char chave_primaria_char[10];
    int keySize = sizeof(PrimaryKey) / sizeof(PrimaryKey[0]);

   

    char caminho_Tabela = caminho(nome_Tabela);
    FILE *arquivoInfo = fopen(caminho_Tabela, "r");

    if (arquivoInfo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;}

   
    char **matriz_clone = malloc(sizeof(char)* nCaracteres); // Reservando Vetor


    while (fgets(matriz_clone, (nCaracteres+1), arquivoInfo)) {
        
    }















 

    /*Partindo da premissa que table é uma matriz, o seguinte for serve somente para recuperar a linha
    a qual o registro com a chave primaria está */

   
 
int rowVerify (char* row, int nCaracteres) {

    int i,a;

    char *matriz_clone = malloc(sizeof(char) * nCaracteres); // Reservando Vetor

    // Verificação de alocação bem-sucedida
    if (matriz_clone == NULL) {
        return -1;}

    static int confirm = 0;
    int exit = 0;

     for (i=0;i<nCaracteres;i++){

        //Garantia que a chave primaria é a que esperamos
        if (exit == 1){break;}
        
        
        if (row[i] == '\0') {
           matriz_clone[i] = '\0';} 
        else {
         matriz_clone[i] = row[i];} // Marca o final da string caso não consiga ler mais caracteres;

        if (matriz_clone[i] == '|'){
            exit++;
            for (a = 0;a<keySize;a++){
                // a em um primeiro momento a precisa ser > 1;Para matriz clone. Isso porque o ultimo numero da suposta chave começa assim.
                // a em um primeiro momento preciso ser = 0; Para tamanhoChave.
                if ((i-1) - a >= 0 && matriz_clone[(i-1)-a] == PrimaryKey[keySize - 1 - a]){confirm++;}
                else{break;}   
             }
            }
            
           }
           free(matriz_clone); // Liberando a memória alocada
           return confirm;
           }
   


/*

matriz[i][j]

Chave| int A | char B | float C

99|    4      PIPOCA    1.4175
98|    4      PIPOCA    1.4175
97|    4      PIPOCA    1.4175

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-===-=-

Chave| int A | char B | float C

99   |   4     PIPOCA   1.4175


Problema: Se a leitura para em cima de um dos numeros da chave primaria. S passar numero de caracteres que a linha da tabela abarca.
Uma fomra de fazer isso é saber a quantidade de caracteres cada coluna vai abarcar e de alguma forma recuperar essa informação cada vez que a tabela
for usada. 

i) Leitura deve começar pelo primeiro caractere de informação.


99|    4      PIPOCA    1.4175
99|    4      PIPOCA    1.4175
99|    4      PIPOCA    1.4175

*/

