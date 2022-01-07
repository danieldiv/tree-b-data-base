#include "file.h"

/**
 * @brief Gera um numero aleatorio inteiro na faixa de 1000 a 9000
 * 
 */
int get_random() { return (1000 + rand() % 9000); }

/**
 * @brief Gera um numero aleatorio inteiro na faixa de 1 a 80
 * 
 */
int get_randomIdade() { return (1 + rand() % 80); }

void writeFile(char *nome, char *valor) {
	FILE *file;
	char path[100];

	strcpy(path, "src/files/clientes/teste.txt");
	// strcat(path, strcat(nome, ".txt"));

	file = fopen(path, "w");

	if(file == NULL) {
		printf("Nao foi possivel abrir o arquivo c1\n");
		return;
	} else {
		fputs(valor, file);
	}
	printf("%s", valor);
	fclose(file);
}

/**
 * @brief Realiza a leitura do arquivo com os nomes dos clientes, o arquivos com os cpfs
 * gerados aleatoriamente e retirados valores repetidos via excel.
 * 
 * A leitura do nome das pessoas possui mais informacoes, sendo necessario tokenizar,
 * estando apenas com o nome, sera adicionado o cpf e a idade gerado aleatoriamente entre 1 e 80
 * 
 * A quantidade de digitos utilizado para os CPFs sao 4, foi gerado valores aleatorio
 * e depois ordenados para facilitar na manutencao da criacao de arquivos.
 * 
 * Os nomes utilizado foi adiquirito da internet
 * 
 * A idade foi gerado randomicamente
 * 
 */
void readFileConcat() {
	FILE *fileDados;
	FILE *fileClientes;
	FILE *fileCPF;

	int cpf[1000];
	int cont = 0;

	int controle = TRUE;
	char nome[10];

	char *pathCPF = (char*)malloc(strlen("src/files/clientes-cpf.txt") * sizeof(char));
	char *pathDados = (char*)malloc(strlen("src/files/clientes-original.txt") * sizeof(char));
	char *pathClientes = (char*)malloc(strlen("src/files/clientes.txt") * sizeof(char));

	char text[100], linha[100], cpf_aux[5];
	char *result, *valor;

	valor = (char*)malloc(200 * sizeof(char));

	strcpy(pathCPF, "src/files/clientes-cpf.txt");
	strcpy(pathDados, "src/files/clientes-original.txt");
	strcpy(pathClientes, "src/files/clientes.txt");

	fileDados = fopen(pathDados, "r");
	fileClientes = fopen(pathClientes, "w");
	fileCPF = fopen(pathCPF, "r");

	if(fileClientes == NULL) {
		printf("Erro ao abrir ou criar arquivo clientes.txt\n");
		return;
	} else {
		if(fileCPF == NULL) {
			printf("Erro ao abrir arquivo clientes-cpf.txt\n");
			return;
		} else {
			while(!feof(fileCPF)) {
				result = fgets(linha, sizeof(linha), fileCPF);

				if(result)
					cpf[cont++] = atoi(linha);
			}
		}

		cont = 0;
		if(fileDados == NULL) {
			printf("Erro ao abrir arquivo clientes-original.txt\n");
			return;
		} else {
			while(!feof(fileDados)) {
				result = fgets(linha, sizeof(linha), fileDados);

				if(result) {
					tokenizar(linha);

					sprintf(text, "%d", get_randomIdade());

					strcat(linha, ",");
					strcat(linha, text);

					sprintf(text, "%d", cpf[cont++]);
					strcpy(cpf_aux, text);

					if(controle) {
						strcpy(cpf_aux, text);
						fputs(strcat(cpf_aux, "-"), fileClientes);

						controle = FALSE;
					}

					strcat(text, ",");
					strcat(valor, strcat(text, strcat(linha, "\n")));

					if(cont % 10 == 0) {
						strcat(nome, "...");
						strcat(nome, cpf_aux);
						fputs(strcat(cpf_aux, "\n"), fileClientes);

						// writeFile(nome, valor);
						valor = (char*)malloc(200 * sizeof(char));
						// printf("\n");

						controle = TRUE;
					}
				}
			}
			printf("cont: %d\n", cont);
		}
	}
	fclose(fileDados);
	fclose(fileClientes);
	fclose(fileCPF);

	free(valor);

	free(pathCPF);
	free(pathDados);
	free(pathClientes);
}

void tokenizar(char *str) {
	const char sep[] = "<> , ' '";
	char *tokens;
	int cont = 0;

	int aux = 0;
	
	tokens = strtok(str, sep);
	
	while(tokens != NULL) {
		if(aux == 1) {
			strcpy(str, tokens);
			return;
		}
        aux = 1;
		tokens = strtok(NULL, sep);
	}
}