#include<stdio.h>
#include <stdlib.h>
#include <string.h>


#include <direct.h>

char* cria_Matriz (char* nome_Tabela){
/*
=-=-=-=-=-=-=-= CRIA PASTA/DIRETORIO DA TABLEA x  =-=-=-=-=-=-=-= 

*/

// Nome da Tabela a ser criada



    int result = _mkdir(nome_Tabela);  // Cria o diretório/Pasta

    if (result == 0) {
        printf("Diretorio criado com sucesso.\n");
    } else {
        perror("Erro ao criar o diretorio");
    }


    // Aloca memória dinamicamente para armazenar a string
    char* nomeDiretorioDin = malloc(strlen(nome_Tabela) + 1);
    if (nomeDiretorioDin != NULL) {
        strcpy(nomeDiretorioDin, nome_Tabela);
    }

    return nomeDiretorioDin;
}






char* cria_coluna (char* nome_coluna,char* nome_tabela){

    
/* 
-=-=-=-=-=-=-=- CRIANDO COLUNA DENTRO DO DIRETORIO -=-=-=-=-=-=-=- 

a) No argumento deve-se passar o nome da tabela (Já criada)
b) Retorna o Diretorio e Nome da coluna;

*/

    char caminhoAtual[1024]; // Para armazenar o caminho do diretório atual
    static char caminhoCompleto[1024]; // Para armazenar o caminho completo do novo diretório

    char nome_coluna_refatorado[200];

    sprintf(nome_coluna_refatorado, "%s.txt",nome_coluna); 

    

    // Obtém o caminho do diretório onde o programa está sendo executado
    if (getcwd(caminhoAtual, sizeof(caminhoAtual)) != NULL) {
        // Combina o caminho atual com o nome do novo diretório
        snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s\\%s\\%s", caminhoAtual,nome_tabela,nome_coluna_refatorado);
        
        // Mostra o caminho completo do novo diretório
        printf("O caminho completo do novo diretorio e: %s\n", caminhoCompleto);
    } else {
        // Exibe uma mensagem de erro se não conseguir obter o caminho atual
        perror("Erro ao obter o caminho atual");
        return 1;
    }

    return caminhoCompleto;

    
}

char* reformulacao (int tamanho, char* caminhoCompleto){

/* 
-=-=-=-=-=-=-=- ADAPTANDO DIRETORIO + NOME DA COLUNA -=-=-=-=-=-=-=- 

a) 
b) 

*/

    
    int parametro = 0;
    int i;

    // Aloca memória dinamicamente para a nova string
    char* copy = malloc(1024 * sizeof(char));

        for(i=0;i<tamanho+1;i++){
    
        if (caminhoCompleto[i] == ('\\') ){
            copy[parametro] = '\\';
            parametro++;
            copy[parametro] = '\\';
            parametro++;

            //printf("CAIU NA CONDICAO\n");
        }
        else{
            copy[parametro] = caminhoCompleto[i];
            parametro++;
        }};

    
    return copy;  }


/* =-=-=-=-=-= REGISTRO'S =-=-=-=-=-=*/

typedef  struct {
    
    int indice_inicial;
    int numero_caracteres;
    int ultimo_indice;
}ColunaInformacao;







int main() {

    /* =-=-=-=-=-=-=- VARIAVEIS =-=-=-=-=-=-=-=*/

    int ultimo_indice_geral = 0;
    int ncaracteres = 0;
    char futurodiretorioCriado[1024];

    /* =--=-=-=-=-=-=-=- CRIANDO DIRETORIO DA TABELA -=-=-=-=-=-=-=-= */

    char nome_Tabela[200];

    printf("Digite o Nome da Tabela:\nOBS: Limite de ate 200 caracteres ");

    fgets(nome_Tabela,199,stdin); //Capturando nome da Tabela

    nome_Tabela[strcspn(nome_Tabela, "\n")] = 0; //Removendo a quebra de linha

    cria_Matriz(nome_Tabela); // Chamando Função

    

    /* =--=-=-=-=-=-=-=- CRIANDO COLUNAS DA TABELA -=-=-=-=-=-=-=-= */

    char copia_Nome_tabela[200];

    while (1){

    char colunaNome[200];
    strcpy(copia_Nome_tabela,nome_Tabela);
   
    printf("DIGITE O NOME DA COLUNA:");

    fgets(colunaNome,199,stdin);
    colunaNome[strcspn(colunaNome, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("NOME DA TABELA: %s\n",nome_Tabela);
    
    char* provisorio_caminho_completo = cria_coluna(colunaNome,copia_Nome_tabela); // Chamando Função

    printf("APOS PASSAR PELA FUNCAO: %s\n",provisorio_caminho_completo);

    char caminhoCompleto [1024];
    if (provisorio_caminho_completo != NULL) {
        // Copia a string de `provisorio_caminho_completo` para `caminhoCompleto`
        strcpy(caminhoCompleto, provisorio_caminho_completo);
    }

    /* =-=-=-=-=-=-=-=-= ADAPTANDO DIRETORIO + NOME DA COLUNA =-=-=-=-=-=-=-=-= */

   

    int i;
    int tamanho = sizeof(caminhoCompleto) / sizeof(caminhoCompleto[0]);

    printf("\n");
    char copy[1024];
    int parametro = 0;

        for(i=0;i<tamanho+1;i++){
    
        if (caminhoCompleto[i] == ('\\') ){
            copy[parametro] = '\\';
            parametro++;
            copy[parametro] = '\\';
            parametro++;

            //printf("CAIU NA CONDICAO\n");
        }
        else{
            copy[parametro] = caminhoCompleto[i];
            parametro++;
        }};

        // Nome do diretório e do arquivo
        const char *caminho = copy;

        // Abre o arquivo no modo de escrita
        FILE *file = fopen(copy, "w");
    
        if (file == NULL) {
            perror("Erro ao criar o arquivo");
            return 1;
        };

    /* =-=-=-=-=-=-=- ATRIBUINDO INFORMAÇÔES A COLUNA =-=-=-=-=-=-=- */ 

    printf("DIGITE O NUMERO DE CARACTERES QUE SUA COLUNA '%s' VAI ABARCAR:\n",colunaNome);
    scanf("%d",&ncaracteres);

    ColunaInformacao colunaN;

    colunaN.indice_inicial = ultimo_indice_geral;
    colunaN.numero_caracteres = ncaracteres;
    colunaN.ultimo_indice = ultimo_indice_geral + ncaracteres;

    ultimo_indice_geral = ultimo_indice_geral + ncaracteres + 1;

    /* =-=-=-=-=-=-=- FAZENDO REGISTRO NO ARQUIVO =-=-=-=-=-=-=- */

    // Abrindo Arquuivo

    FILE *arquivo = fopen(caminho, "a+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(arquivo, "%d\n",colunaN.indice_inicial);
    fprintf(arquivo, "%d\n",colunaN.numero_caracteres);
    fprintf(arquivo, "%d\n",colunaN.ultimo_indice);

    fclose(arquivo);

    printf("indice incial: %d\n",colunaN.indice_inicial);
    printf("Bits para Registro: %d\n",colunaN.numero_caracteres);
    printf("Ultimo indice: %d\n",colunaN.ultimo_indice);




    /* =-=-=-=-=-=-= SAI DA LAÇO =-=-=-=-=-=-= */

    int indicador = 0;

    printf("SE DESEJA ADICIONAR MAIS COLUNAS,APERTE '1'. SE NAO DIGITE UM NUMERO DIFERENTE DE 1.\n");
    scanf("%d",&indicador);
    getchar();

    if (indicador != 1){
        int tamanho = sizeof(caminho) / sizeof(caminho[0]); 
        strcpy(futurodiretorioCriado, caminho);
            break;}
    }

    
    
    
    // -=-=-=-=-=-=-=-=-=- LEITURA DO ARQUIVO -=-=-=-=-=-=-=-=-=- 

    
 
   // =-=-=-=- CRIANDO TABELA COM INFORMAÇÕES =-=-=-=-  

   

    // =-=-=-=-= Abrindo Aquivo e Iniciando processo de leitura =-=-=-=-=-= 

    FILE *arquivo = fopen(futurodiretorioCriado, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    printf("Iniciando Processo de Leitura do arquivo\n");

    //A PARTIR DAQUI

    char primeiro_parametro[100];
    char segundo_parametro[100];
    char terceiro_parametro[100];

    fgets(primeiro_parametro, sizeof(primeiro_parametro), arquivo);
    fgets(segundo_parametro, sizeof(segundo_parametro), arquivo);
    fgets(terceiro_parametro, sizeof(terceiro_parametro), arquivo);

    fclose(arquivo);

    printf("PRIMEIRO: %s\n", primeiro_parametro);
    printf("SEGUNDO: %s\n", segundo_parametro);
    printf("TERCEIRO: %s\n", terceiro_parametro);

    // Converte as strings lidas para inteiros
    int numero01 = atoi(primeiro_parametro);
    int numero02 = atoi(segundo_parametro);
    int numero03 = atoi(terceiro_parametro);

     printf("PRIMEIRO: %d\n", numero01);
    printf("SEGUNDO: %d\n", numero02);
    printf("TERCEIRO: %d\n", numero03);




    /*int i,j;
    printf("Iniciando Processo de Leitura da Matriz\n");

    for (i = 0; i < novas_linhas-1; i++) {
    for (j = 0; matrizDeRetorno[i][j] != '\0'; j++) {
        printf("%c", matrizDeRetorno[i][j]);
    }
    printf("PROXIMA LINHA\n");  // Para imprimir uma nova linha entre as linhas da matriz
}

printf("Terminando Processo de Leitura da Matriz\n");


    for (i = 0; i < novas_linhas; i++) {
    free(matrizDeRetorno[i]);}

    free(matrizDeRetorno);*/
 

    /* =-=-=-=-=-= INICANDO PROCESSO DE LEITURA DA MATRIZ =-=-=-=-=-=*/

    /*printf("Iniciando Processo de Leitura da Matriz\n");
    printf("%c",matrizDeRetorno[1][1]);
    printf("%c",matrizDeRetorno[1][2]);
    printf("%c",matrizDeRetorno[1][3]);
    printf("%c",matrizDeRetorno[1][4]);
    printf("%c",matrizDeRetorno[1][5]);

    printf("PAREI");

    int variavelD,i;

     for (variavelD = 0; variavelD < novas_linhas - 1; variavelD++) {
        for (i = 0; matrizDeRetorno[variavelD][i] != '\0';i++){
        printf("%c",matrizDeRetorno[variavelD][i]);}
    }

    free(matrizDeRetorno);*/

    return 0;
}
