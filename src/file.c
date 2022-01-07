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

void writeFile(int start, int end, char *valor) {
	FILE *file;
	char *path = (char*)malloc((strlen(PATH_CLIENTES) + 15) * sizeof(char));

	char aux_start[20], aux_end[20];

	sprintf(aux_start, "%d", start);
	sprintf(aux_end, "%d", end);

	strcpy(path, PATH_CLIENTES);
	strcat(aux_start, "...");
	strcat(path, strcat(aux_start, strcat(aux_end, ".txt")));

	file = fopen(path, "w");

	if(file == NULL) {
		printf("Nao foi possivel abrir o arquivo c1\n");
		return;
	} else {
		fputs(valor, file);
	}
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
void readFileConcat(Lista *lista) {
	FILE *fileDados;
	FILE *fileCPF;

	Item item;
	item.valor = (char*)malloc(200 * sizeof(char));

	int cpf[1000];
	int cont = 0;

	int controle = TRUE;

	char *pathCPF = (char*)malloc(strlen("src/files/clientes-cpf.txt") * sizeof(char));
	char *pathDados = (char*)malloc(strlen("src/files/clientes-original.txt") * sizeof(char));

	char text[100], linha[100];
	char *result;

	strcpy(pathCPF, "src/files/clientes-cpf.txt");
	strcpy(pathDados, "src/files/clientes-original.txt");

	fileDados = fopen(pathDados, "r");
	fileCPF = fopen(pathCPF, "r");

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

				if(controle) {
					item.cpfStart = cpf[cont-1];
					controle = FALSE;
				}

				strcat(text, ",");
				strcat(item.valor, strcat(text, strcat(linha, "\n")));

				if(cont % 10 == 0) {
					item.cpfEnd = cpf[cont-1];

					LInsere(lista, item);

					item.valor = (char*)malloc(200 * sizeof(char));
					controle = TRUE;
				}
			}
		}
		printf("cont: %d\n", cont);
	}
	fclose(fileDados);
	fclose(fileCPF);

	free(pathCPF);
	free(pathDados);
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