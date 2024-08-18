# Requisitos do projeto

## 1. Criar um tabela

a. os tipos de dados para as colunas poderão ser os tipos primitivos em
C ( char, int, float e double) e strings -> Feito 
b. os valores deverão ser armazenados em arquivo -> Feito 
c. na criação da tabela deverá ser solicitado um nome de coluna para
ser a chave primária -> Feito 
  - i. a chave primária deverá ser obrigatoriamente do tipo inteiro
  sem sinal -> Feito 

## 2. Listar todas as tabelas

a. deverá mostrar para o usuário as tabelas existentes -> Feito 

## 3. Criar uma nova linha na tabela

a. Usuário deve informar o nome da tabela -> Feito
b. sistema deve solicitar os valores de cada uma das colunas -> Feito
c. sistema deve verificar a chave primária -> Feito
- i. Em uma tabela deve existir um e apenas um valor de chave
  primária. Se o usuário informar uma chave que já existe,
  sistema deve emitir uma mensagem de erro e não deve inserir
  o registro

## 4. Listar todos os dados de uma tabela

a. Usuário deve informar qual a tabela para serem listados os dados 
b. os dados deverão ser obtidos a partir do arquivo que armaz

## 5. Pesquisar valor em uma tabela

a. Usuário deverá informar o nome da tabela onde realizará a pesquisa
b. Sistema deverá fornecer as colunas disponíveis na tabela o usuário
deverá selecionar uma delas
c. Sistema deverá solicitar o valor para pesquisar, disponibilizando
algumas opções
- i. valores maior que o valor informado
- ii. valores maior ou igual que o valor informado
- iii. valores igual o valor informado
- iv. valores menor que o valor informado
- v. valores menor ou igual que o valor informado
- vi. valores próximo ao valor informado
  - 1. se aplica apenas se a coluna for do tipo string

## 6. Apagar uma tupla (registro ou linha) de uma tabela

a. Usuário deve informar o nome da tabela e a chave primária da tupla a
ser apagada

## 7. Apagar uma tabela

a. usuário deverá fornecer o nome da tabela a ser apagada -> Feito

