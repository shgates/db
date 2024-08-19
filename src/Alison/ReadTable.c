#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Retorna uma String com o diretorio onde o arquivo a ser lido está
char caminho (char* nome_Tabela){
    char caminhoTabela[1024];
    snprintf(caminhoTabela, sizeof(caminhoTabela), "./%s.txt",nome_Tabela);

    return caminhoTabela;}

char readTable (char* nome_tabela, int nCaracteres) {

    char caminho_tabela = caminho(nome_tabela);
    FILE *arquivoInfo = fopen(caminho_tabela, "r");

    if (arquivoInfo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;}

    char *matriz_clone = malloc(sizeof(char)* nCaracteres); // Reservando Vetor. 

    while (fgets(matriz_clone, (nCaracteres+1), arquivoInfo)) {
       printf("%s",matriz_clone);
       memset(matriz_clone, 0, nCaracteres + 1); // Limpando o conteúdo da matriz
     }

    free(matriz_clone);  // Liberando a memória alocada após o loop
    fclose(arquivoInfo); // Fechando o arquivo
    return 0;
    }















