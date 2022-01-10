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
		printf("Nao foi possivel abrir o arquivo %s\n", aux_start);
		return;
	} else {
		fputs(valor, file);
	}
	fclose(file);
}

void readFileConcat(Lista *lista) {
	FILE *fileDados;
	FILE *fileCPF;
	FILE *fileIntervalo;

	Item item;
	item.valor = (char*)malloc(200 * sizeof(char));

	int cpf[1000];
	int cont = 0;

	int controle = TRUE;

	char *pathCPF = (char*)malloc(50 * sizeof(char));
	char *pathDados = (char*)malloc(50 * sizeof(char));
	char *pathIntervalo = (char*)malloc(50 * sizeof(char));

	char text[100], linha[100], intervalo[10];
	char *result;

	strcpy(pathCPF, "src/files/clientes-cpf.txt");
	strcpy(pathDados, "src/files/clientes-original.txt");
	strcpy(pathIntervalo, "src/files/clientes-intervalo.txt");

	fileDados = fopen(pathDados, "r");
	fileCPF = fopen(pathCPF, "r");
	fileIntervalo = fopen(pathIntervalo, "w");

	if(fileIntervalo == NULL) {
		printf("Erro ao abrir arquivo clientes-intervalo.txt\n");
		return;
	}
	else {
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
					strcpy(intervalo, text);

					if(controle) {
						item.cpfStart = cpf[cont-1];
						controle = FALSE;
						
						fputs(strcat(intervalo, "\n"), fileIntervalo);
					}

					strcat(text, ",");
					strcat(item.valor, strcat(text, strcat(linha, "\n")));

					if(cont % 10 == 0) {
						item.cpfEnd = cpf[cont-1];

						LInsere(lista, item);
						fputs(strcat(intervalo, "\n"), fileIntervalo);

						item.valor = (char*)malloc(200 * sizeof(char));
						controle = TRUE;
					}
				}
			}
			// printf("cont: %d\n", cont);
		}
	}
	fclose(fileDados);
	fclose(fileCPF);
	fclose(fileIntervalo);

	free(pathCPF);
	free(pathDados);
	free(pathIntervalo);
}

void readFileIntervalo(Pagina **p) {
	FILE *file;
	char *path = (char*)malloc(50 * sizeof(char));

	char *result, linha[100], text[10];
	Record r;
	int aux = TRUE;

	strcpy(path, "src/files/clientes-intervalo.txt");

	file = fopen(path, "r");

	if(file == NULL) {
		printf("Nao foi possivel abrir o arquivo clientes-intervalo.txt\n");
		return;
	} else {
		while(!feof(file)) {
			result = fgets(linha, sizeof(linha), file);

			if(result) {
				if(aux) {
					r.key = atoi(linha);
					aux = FALSE;
				} else {
					r.limite = atoi(linha);
					r.arquivo = (char*)malloc(20 * sizeof(char));					
					Insere(p, r);

					aux = TRUE;
				}
			}
		}
	}

	fclose(file);
	free(path);
}

void readFileClientes(Record *r, Cliente *c, int *aux, char *clientes) {
	FILE *file;

	char *path = (char*)malloc(50 * sizeof(char));
	char *str = (char*)malloc(50 * sizeof(char));
	c->nome = (char*)malloc(20 * sizeof(char));

	char *result, linha[100];
	int controle = TRUE;

	strcpy(path, PATH_CLIENTES);
	strcat(path, r->arquivo);
	strcat(path, ".txt");

	file = fopen(path, "r");
	strcpy(clientes, "");

	if(file == NULL) {
		printf("Nao foi possivel abrir o arquivo %s!\n", r->arquivo);
		return;
	} else {
		while(!feof(file)) {
			result = fgets(linha, sizeof(linha), file);

			if(result) {
				strcpy(str, linha);
				
				if(!(*aux))
					tokenizarClientes(linha, c, aux, &controle);
				if(controle)
					strcat(clientes, str);
				else
					controle = TRUE;
			}
		}
	}
	fclose(file);
	free(path);
}

int get_quantClientes(char *arquivo) {
	FILE *file;

	char *path = (char*)malloc(50 * sizeof(char));

	char *result, linha[100];
	int quant = 0;

	strcpy(path, PATH_CLIENTES);
	strcat(path, arquivo);
	strcat(path, ".txt");

	file = fopen(path, "r");

	if(file == NULL) {
		printf("Nao foi possivel abrir o arquivo %s!\n", path);
		return -1;
	} else {
		while(!feof(file)) {
			result = fgets(linha, sizeof(linha), file);

			if(result)
				quant++;
		}
	}
	fclose(file);

	return quant;
}

void tokenizar(char *str) {
	const char sep[] = "<> , ' '";
	char *tokens;
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

void tokenizarClientes(char *str, Cliente *c, int *aux, int *remover) {
	const char sep[] = ",";
	char *tokens;

	int controle = 0;
	
	tokens = strtok(str, sep);
	
	while(tokens != NULL) {
		if(controle == 0) {
			if((atoi(tokens) != c->cpf)) {
				*aux = FALSE;
				return;
			}
			*remover = FALSE;
			*aux = TRUE;
		} else if(controle == 1) {
			strcpy(c->nome, tokens);
		} else if(controle == 2) {
			c->idade = atoi(tokens);
		}
		controle++;
		tokens = strtok(NULL, sep);
	}
}

// int get_quantClientes(char *path) {
// 	FILE *file;
// 	// char *path = (char*)malloc(50 * sizeof(char));

// 	char *result, linha[100];
// 	int quant = 0;

// 	// strcpy(path, r->arquivo);
// 	// strcat(path, strcat(r->arquivo, ".txt"));

// 	file = fopen(path, "r");

// 	if(file == NULL) {
// 		printf("Nao foi possivel abrir o arquivo %s!\n", path);
// 		return -1;
// 	} else {
// 		while(!feof(file)) {
// 			result = fgets(linha, sizeof(linha), file);

// 			if(result)
// 				quant++;
// 		}
// 	}
// 	fclose(file);
// 	free(path);

// 	return 1;
// }