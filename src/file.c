#include "file.h"


/**
 * @brief Gera um numero aleatorio inteiro na faixa de 1 a 80
 * utilizado no metodo readFileConcat para gerar a idade
 * tambem utilizado no main quando insere um novo cliente para gerar um valor aleatorio e a idade
 * 
 */
int get_randomIdade() { return (1 + rand() % 80); }

/**
 * @brief writeFile: funcao utilizada para criar um arquivo com informacao
 * 
 * utilizado pelo metodo createFile localizado main, que cria arquivo atravez de uma lista
 * tambem utilizado no main quando remove um valor do arquivo e cria um outro arquivo com o mesmo nome
 * tambem utilizado no main quando adiciona um valor no arquivo e cria um outro arquivo com o mesmo nome
 * 
 * para as duas chamadas acima, os arquivo sao removidos antes de criar novamente
 * 
 * @param start valor a ser utilizado para dar nome ao arquivo
 * @param end valor a ser utilizado para dar nome ao arquivo
 * @param valor sera o valor a ser adicionado no arquivo
 */
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

/**
 * @brief readFileConcat: funcao utilizada para concatenar as informacoes de arquivos separados em outro arquivo
 * 
 * Esta funcao e realizada apenas uma vez no main quando o programa compilado
 * 
 * @param lista ponteiro de lista que sera utilizado no main com as informacoes concatenadas
 */
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

/**
 * @brief readFileIntervalo: funcao utilizada para inserir os valores de intervalos dos arquivos na arvore B
 * 
 * este metodo e executado quando seleciona a opcao 1 do switch no main
 * 
 * @param p arvore B que sera inserido os arquivos
 */
void readFileIntervalo(Pagina **p) {
	FILE *file;
	char *path = (char*)malloc(50 * sizeof(char));

	char *result, linha[100];
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

/**
 * @brief readFileClientes: funcao responsavel para abrir um determinado arquivo da pasta clientes
 * 
 * @param r contem as informacoes do no da arvore em questao e nome do arquivo que sera aberto
 * @param c salva as informacoes do cliente para utilizar no main
 * @param aux controle para verificar se encontrou um cpf dentro do arquivo
 * @param clientes utilizado para mesclar as informacoes apoz remocao ou insersao de um cliente
 * @param nome contem as informacoes do cliente quando for inserido
 * @param valorInsert utilizado quando insere um novo cliente, para verificar com os cpfs cadastrados
 */
void readFileClientes(Record *r, Cliente *c, int *aux, char *clientes, char *nome, int valorInsert) {
	FILE *file;

	char *path = (char*)malloc(50 * sizeof(char));
	char *str = (char*)malloc(50 * sizeof(char));
	c->nome = (char*)malloc(20 * sizeof(char));

	char *result, linha[100];
	int controle = TRUE, nomeAdicionado = TRUE;
	int cpf = 0;

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
					tokenizarClientes(linha, c, aux, &controle, &cpf);
				if(controle) {
					if(valorInsert < cpf && nomeAdicionado) {
						strcat(clientes, nome);
						nomeAdicionado = FALSE;
					}
					strcat(clientes, str);
				}
					
				else 
					controle = TRUE;
			}
		}
	}
	fclose(file);
	free(path);
}

/**
 * @brief quantClientes: funcao utilizada para contabilizar a quantidade de valores dentro do arquivo
 * 
 * utilizado no main quando pesquisa ou remove um valor arquivo, para verificar se o arquivo nao esta vazio
 * utilizado no main quando adiciona um valor no arquivo, para verificar se o arquivo esta cheio
 * 
 * @param arquivo string com o nome do arquivo para ser aberto
 * @return int 
 */
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

/**
 * @brief tokenizar: funcao utilizada para quebrar a string pelo separador ( , )
 * 
 * utilizada pelo readFileConcat quando abre o arquivo de nomes dos clientes, que possui informacoes que nao sao necessarias, apenas o nome
 * 
 * @param str string a ser quebrada
 */
void tokenizar(char *str) {
	const char sep[] = ",";
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