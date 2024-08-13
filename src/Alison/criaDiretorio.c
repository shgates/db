#include<stdio.h>
#include <stdlib.h>
#include <string.h>


#include <direct.h>

int main() {

    /* =--=-=-=-=-=-=-=- CRIANDO DIRETORIO DA TABELA -=-=-=-=-=-=-=-= */

    // Nome da Tabela a ser criada
    char nomeDiretorio[200];
    printf("Digite o Nome da Tabela:");
    fgets(nomeDiretorio,199,stdin);
    nomeDiretorio[strcspn(nomeDiretorio, "\n")] = 0;
    const char *dirName = nomeDiretorio;

    // Cria o diretório
    int result = _mkdir(dirName);

    if (result == 0) {
        printf("Diretorio criado com sucesso.\n");
    } else {
        perror("Erro ao criar o diretorio");
    }

    char caminhoAtual[1024]; // Para armazenar o caminho do diretório atual
    char caminhoCompleto[1024]; // Para armazenar o caminho completo do novo diretório

    char colunaNome[200];
    char newnameColun[200];
    printf("DIGITE O NOME DA COLUNA:");
    fgets(colunaNome,199,stdin);
    colunaNome[strcspn(colunaNome, "\n")] = '\0'; // Remove o caractere de nova linha
    sprintf(newnameColun, "%s.txt",colunaNome); 

    

    // Obtém o caminho do diretório onde o programa está sendo executado
    if (getcwd(caminhoAtual, sizeof(caminhoAtual)) != NULL) {
        // Combina o caminho atual com o nome do novo diretório
        snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s\\%s\\%s", caminhoAtual, dirName,newnameColun);
        
        // Mostra o caminho completo do novo diretório
        printf("O caminho completo do novo diretorio e: %s\n", caminhoCompleto);
    } else {
        // Exibe uma mensagem de erro se não conseguir obter o caminho atual
        perror("Erro ao obter o caminho atual");
        return 1;
    }

   

    int i;
    int tamanho = sizeof(caminhoCompleto) / sizeof(caminhoCompleto[0]);

    /*printf("DENTRO DO FOR\n");

    for(i=0;i<tamanho+1;i++){
        if (caminhoCompleto[i] == '\0'){
            break;
        }
        printf("%c",caminhoCompleto[i]);
    }*/

    printf("\n");
    char copy[1024];
    int param = 0;

        for(i=0;i<tamanho+1;i++){
    
        if (caminhoCompleto[i] == ('\\') ){
            copy[param] = '\\';
            param++;
            copy[param] = '\\';
            param++;

             printf("CAIU NA CONDICAO\n");
        }
        else{
            copy[param] = caminhoCompleto[i];
            param++;
        }};

        // Nome do diretório e do arquivo
        const char *caminho = copy;

        // Abre o arquivo no modo de escrita
        FILE *file = fopen(caminho, "w");
    
        if (file == NULL) {
            perror("Erro ao criar o arquivo");
            return 1;
        }

        /*printf("DENTRO DO SEGUNDO FOR\n");

         for(i=0;i<tamanho+1;i++){

            if (copy[i] == '\0'){
                printf("\nVAI DE BREAK\n");
                break;}

            printf("%c",copy[i]);}*/



    return 0;
}
