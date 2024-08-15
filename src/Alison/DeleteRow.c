char delete_Row(char* chavePrimaria, char *table, int nRows) {

// Se chavePrimaria for recebida como char temos que isolar cada caractere em uma matriz a parte
// Se chavePrimaria for recebida como inteiro, de qualquer forma temos que comparar caractere por caractere, o que não da pra fazer com interio


    int i,j,a;
    int linha;
    int row,column,confirm=0;
    int tamanhoChave = sizeof(chavePrimaria) / sizeof(chavePrimaria[0]); 

    char chave_primaria_char[10];

   
    char **matriz_clone = (char **)malloc(1 * sizeof(char *)); // Reservando linhas
    matriz_clone[0] = (char *)malloc(150 * sizeof(char)); // Reservando Colunas

    /*Partindo da premissa que table é uma matriz, o seguinte for serve somente para recuperar a linha
    a qual o registro com a chave primaria está */
    for (i=1;i<nRows;i++){
     for (j=0;j<150;j++){
        if (confirm = tamanhoChave){break;}
        
        if (fscanf(table, "%c", &matriz_clone[i-1][j]) != 1){
        matriz_clone[i - 1][j] = '\0';} // Marca o final da string caso não consiga ler mais caracteres;

        else if (matriz_clone[i - 1][j] = '|'){
            for (a = 0;a<tamanhoChave;a++){
                // a em um primeiro momento a precisa ser > 1;Para matriz clone. Isso porque o ultimo numero da suposta chave começa assim.
                // a em um primeiro momento preciso ser = 0; Para tamanhoChave.
                if (matriz_clone[i - 1][j-(a+1)] = chavePrimaria[tamanhoChave - a]){confirm++;}
                else{break;}
                
            }
            if (confirm = tamanhoChave){
                linha = i - 1;}}}}
   
}

/*

matriz[i][j]

Chave| int A | char B | float C

99   |   4     PIPOCA   1.4175
98   |   4     PIPOCA   1.4175
97   |   4     PIPOCA   1.4175

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-===-=-

Chave| int A | char B | float C

99   |   4     PIPOCA   1.4175
98   |   4     PIPOCA   1.4175
97   |   4     PIPOCA   1.4175  

Problema: Se a leitura para em cima de um dos numeros da chave primaria 
*/

