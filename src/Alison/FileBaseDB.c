#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Função para criar uma pasta (tabela)
void criarTabela (const char *nomeTabela){
    //Cria Pasta/Diretorio
    mkdir(nomeTabela);

    // Criar o arquivo infoMAIS e inicializar com 000
    char caminhoInfoMAIS[1024];
    snprintf(caminhoInfoMAIS, sizeof(caminhoInfoMAIS), "%s/infoMAIS.txt", nomeTabela);
    FILE *arquivoInfo = fopen(caminhoInfoMAIS, "w");
    if (arquivoInfo) {
        fprintf(arquivoInfo, "000");
        fclose(arquivoInfo);
    }}

// Função para criar uma coluna (subpasta)
void criarColuna(const char *nomeTabela, const char *nomeColuna) {
    char caminho[1024];
    snprintf(caminho, sizeof(caminho), "%s/%s", nomeTabela, nomeColuna);
    mkdir(caminho);
}

int main() {

    printf("Digite o nome da Tabela:\nOBS: Limite de 200 caracteres.\n");
    char nome_Tabela[200];
    fgets(nome_Tabela,199,stdin);
    
    // Limpar o buffer do fgets()
    if (nome_Tabela[strlen(nome_Tabela) - 1] == '\n') {
        nome_Tabela[strlen(nome_Tabela) - 1] = '\0';
    } else {
        // Caso o buffer não termine com '\n', esvazie o buffer manualmente
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // Criar tabela "Clientes"
    criarTabela(nome_Tabela);

    // Criar colunas
    // a) Primeiro parametro: Nome da tabela.
    // b) Segundo parametro: Nome da Coluna.

    while (1)
    {
    
    printf("Digite o nome da Coluna:\nOBS: Limite de 200 caracteres.\n");
     char nome_Coluna[200];
     fgets(nome_Coluna,199,stdin);

      if (nome_Coluna[strlen(nome_Coluna) - 1] == '\n') {
            nome_Coluna[strlen(nome_Coluna) - 1] = '\0';
        } else {
            // Caso o buffer não termine com '\n', esvazie o buffer manualmente
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

     criarColuna(nome_Tabela, nome_Coluna);

     printf("SE DESEJA ADICIONAR MAIS UMA COLUNA, TECLE '1'. SE DESEJA FINALIZAR TECLE QUALQUER NUMERO DIFERENTE DE '1'");
     int parametro = 0;
     scanf("%d",&parametro);
     getchar();

     if (parametro != 1){
            break;}
    }



    

    return 0;}
