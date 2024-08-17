#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Função para criar uma pasta (tabela)
void criarTabela (const char *nomeTabela){
    //Cria Pasta/Diretorio
    mkdir(nomeTabela);

    
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

void criarArquivoRegistro(int chavePrimaria, char *informacao, const char *tabela, const char *coluna) {
    // Construir o caminho completo do diretório onde o arquivo será criado
    char caminho[512];
    snprintf(caminho, sizeof(caminho), "./%s/%s/%d.txt", tabela, coluna, chavePrimaria);

    // Criar e abrir o arquivo para escrita
    FILE *arquivo = fopen(caminho, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo %s\n", caminho);
        return;
    }

    // Escrever a informação no arquivo
    fprintf(arquivo, "%s", informacao);

    // Fechar o arquivo
    fclose(arquivo);

    printf("Arquivo criado e informação escrita com sucesso em %s\n", caminho);
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

    /* =-=-=-=-=-=-=-= CRIANDO COLUNA =-=-=-=-=-=-=-= */

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

    /*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
    char infoamacao[500];
    printf("Digite o nome da Coluna para registrar informação:\nOBS: Limite de 200 caracteres.\n");
    char nome_Coluna[200];
    fgets(nome_Coluna,199,stdin);

    // Remover o caractere de nova linha ('\n') inserido por fgets, se presente
    if (nome_Coluna[strlen(nome_Coluna) - 1] == '\n') {
        nome_Coluna[strlen(nome_Coluna) - 1] = '\0';
    }

    printf("Digite a informacao que deve ser registrada:\n");
    fgets(infoamacao,499,stdin);
     // Remover o caractere de nova linha ('\n') inserido por fgets, se presente
    if (infoamacao[strlen(infoamacao) - 1] == '\n') {
        infoamacao[strlen(infoamacao) - 1] = '\0';
    }



    criarArquivoRegistro(1,infoamacao,nome_Tabela,nome_Coluna);

  






    return 0;}
