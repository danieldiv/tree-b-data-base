# Arvore B - Banco de Dados

## Informacoes

- 1000 dados de entrada

- cada dado possui (nome, idade, cpf): clientes

- cada pagina possui 10 dados por arquivo, um total de 100 arquivos

- m = 2, minino é igual a m-1 e maximo é igual a (m * 2) - 1

  - minino: 1 | maximo: 3

## Base de dados

- A base de dados com o nome pode ser encontrada em:

  - https://basedosdados.org/dataset/br-ibge-nomes-brasil

## Criacao dos arquivos

- Ao executar a opcao XXX e feita a leitura do arquivo "clientes-cpf.txt", "clientes-original.txt" e a criacao caso nao exista do arquivo "clientes-intervalo.txt".

- Caso a pasta clientes esteja vazia, descomente as linhas 16 e 17 para criacao dos arquivos.

## Remocao de cliente

- A remocao e feita removendo o arquivo para cria-lo novamente sem o cliente excluido