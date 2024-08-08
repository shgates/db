#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef  struct {
    char nome_Coluna[50];
    int parametro_Inicial;
    int bitRegistro;
    int caracteresTotais;
    int ultimoIndice;
}ColunaInformacao;



typedef  struct {
    char nome_Tabela[200];
    int ultimoRegistroPK;
}Tabela;

int main () {

    char nome_Coluna[51];
    char nome_Tabela[100];
    int i,parametro,ultimoParametro=0,indiceDaColuna = 0;
    int nCaracteres = 0,nColunas = 0;

        /* 

        i) O 'ultimoParametro' descreve o numeral que representa o limite de uma coluna.
        Limite nesse caso se refere até onde os caracteres de uma coluna se estende.

        ii) A variavel 'parametro' norteia se o úsuario que continuar ou não inserindo colunas.

        */
    ColunaInformacao* tabelaAUX = NULL;

    printf("DIGITE O NOME DA TABELA:\n");
    fgets(nome_Tabela,99,stdin);
    nome_Tabela[strcspn(nome_Tabela, "\n")] = '\0'; // Remove o caractere de nova linha

    char nome_arquivo[100]; // Array para armazenar o nome do arquivo completo
    // Cria o nome do arquivo dinamicamente
    sprintf(nome_arquivo, "%s.txt", nome_Tabela);
    

    while (1){

    int totalCarcateresRelativos = 0;

    
    memset(nome_Coluna, 0, sizeof(nome_Coluna));

    printf("DIGITE O NOME DA COLUNA:\n");
    fgets(nome_Coluna,50,stdin);
    
    // Remove o caractere de nova linha, se presente
    nome_Coluna[strcspn(nome_Coluna, "\n")] = '\0';

  
    printf("DIGITE O NUMERO DE CARACTERES QUE SUA COLUNA '%s' VAI ABARCAR:\n",nome_Coluna);
    scanf("%d",&nCaracteres);

    ultimoParametro = ultimoParametro + nCaracteres + 1;

    ColunaInformacao colunaN;

    totalCarcateresRelativos = 
    + sizeof(ultimoParametro)
    + sizeof(nCaracteres)
    + 60 + 150 + 6;


    /* Defindo parametros do REGISTRO*/

    strcpy(colunaN.nome_Coluna,nome_Coluna);
    colunaN.parametro_Inicial = ultimoParametro - nCaracteres;
    colunaN.bitRegistro = nCaracteres;
    colunaN.caracteresTotais = totalCarcateresRelativos + sizeof(totalCarcateresRelativos);

    indiceDaColuna++;
    nColunas++;


    /* REDIMENSIONANDO O TAMANHO DA MATRIZ AUXILIAR */

    tabelaAUX = (ColunaInformacao*)realloc(tabelaAUX, nColunas * sizeof(ColunaInformacao));
    tabelaAUX[nColunas - 1] = colunaN;

    /*-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-*/
    

    printf("SE DESEJA ADICIONAR MAIS COLUNAS,APERTE '1'. SE NAO DIGITE UM NUMERO DIFERENTE DE 1.\n");
    scanf("%d",&parametro);
    getchar();

    if (parametro != 1)
    {
        break;}}

    for (i=0;i < 1;i++){
        for (i=0;i < nColunas;i++){
            printf("Nome da Coluna: %d - %s\n",tabelaAUX[i].caracteresTotais,tabelaAUX[i].nome_Coluna);
            printf("Parametro De Inicial: %d\n",tabelaAUX[i].parametro_Inicial);
            printf("Bits para Registro: %d\n",(tabelaAUX[i].bitRegistro));
            
        }}
    


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- NESTE PONTO =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

   // Salvando os dados no arquivo
    FILE *arquivo = fopen(nome_arquivo, "a+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    for (i = 0; i < nColunas; i++) {
        fprintf(arquivo, "Nome da Coluna: %s - %d pP\n",tabelaAUX[i].nome_Coluna,tabelaAUX[i].caracteresTotais);
        fprintf(arquivo, "Parametro De Inicial: %d pP\n",tabelaAUX[i].parametro_Inicial);
        fprintf(arquivo, "Bits para Registro: %d pXP\n",tabelaAUX[i].bitRegistro);
    }

    fclose(arquivo);
    
    // Liberando a memória alocada
    free(tabelaAUX);


    /* -=-=-=-=-=-=-=-=-=- LEITURA DO ARQUIVO -=-=-=-=-=-=-=-=-=- */

    int novas_linhas = 1;
 


    /* =-=-=-=- CRIANDO MATRIZ DINAMICA =-=-=-=-  */

    char **matrizDeRetorno = (char **)malloc(1 * sizeof(char *)); // Reservando linhas
    matrizDeRetorno[0] = (char *)malloc(150 * sizeof(char)); // Reservando Colunas

    /* =-=-=-=-= Abrindo Aquivo e Iniciando processo de leitura =-=-=-=-=-= */

    FILE *arquivoREC = fopen(nome_arquivo, "r");

     if (arquivoREC == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return 1;
    }

    printf("Iniciando Processo de Leitura do arquivo\n");


    for (i=0;i<150;i++){


      if (fscanf(arquivoREC, "%c", &matrizDeRetorno[novas_linhas - 1][i]) != 1) {
        matrizDeRetorno[novas_linhas - 1][i] = '\0';} // Marca o final da string caso não consiga ler mais caracteres;

      printf("Caractere lido: %c\n",matrizDeRetorno[novas_linhas - 1][i]);

      if(matrizDeRetorno[novas_linhas -1 ][i] == 'P' && i > 0 && matrizDeRetorno[novas_linhas -1][i-1] == 'p'){
        printf("ENTORU NO VERIFICADOR DE QUEBRA DE LINHAS\n");
        matrizDeRetorno[novas_linhas - 1][i+1] = '\0';

            novas_linhas++;
  
           // Redimensionando o número de linhas
           printf("O novo numero de linhas sera: %d\n",novas_linhas);
           printf("O indice dessa nova linha sera: %d\n",novas_linhas - 1);
            matrizDeRetorno = (char **)realloc(matrizDeRetorno, novas_linhas * sizeof(char *));
             for (int i = (novas_linhas - 1); i < novas_linhas; i++) {
              printf("Valor de i: %d\n", i);
              matrizDeRetorno[novas_linhas -1] = (char *)malloc(150 * sizeof(char));}}


      if(matrizDeRetorno[novas_linhas - 1][i] == 'P'
       && i > 2 && 
       matrizDeRetorno[novas_linhas - 1][i-1] == 'X' 
       && matrizDeRetorno[novas_linhas - 1][i-2] == 'p')
       {  printf("SINAL DE PARADA\n");
            matrizDeRetorno[novas_linhas - 1][i] = '\0';
            break;}
              
              
              
};

fclose(arquivoREC);


/* =-=-=-=-=-= INICANDO PROCESSO DE LEITURA DA MATRIZ =-=-=-=-=-=*/

    printf("Iniciando Processo de Leitura da Matriz\n");

    int a;
   
     for (a = 1; a < novas_linhas - 1; a++) {
        printf("a=%d\n",a);
        for (i = 0; matrizDeRetorno[a][i] != '\0';i++){
        printf("%c",matrizDeRetorno[a][i]);}
    }

    free(matrizDeRetorno);

    fclose(arquivoREC);
    

    return 0;
}