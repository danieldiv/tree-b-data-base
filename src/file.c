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

/**
 * @brief Arquivos
 * 
 * A quantidade de digitos utilizado para os CPFs sao 4, foi gerado valores aleatorio
 * e depois ordenados para facilitar na manutencao da criacao de arquivos.
 * 
 * Os nomes utilizado foi adiquirito da internet
 * 
 * A idade foi gerado randomicamente
 * 
 */
void readFileInput() {
	FILE *file;
	FILE *fileClientes;
	FILE *fileCPF;

	int cpf[1000];

	char linha[100];
	char pathCPF[100];
	char nome[100];
	char text[20];
	char *result;

	int cont = 0;
	int n;

	strcpy(pathCPF, "src/files/clientes-cpf.txt");
	strcpy(linha, "src/files/clientes-original.txt");
	strcpy(nome, "src/files/clientes.txt");

	file = fopen(linha, "r");
	fileClientes = fopen(nome, "w");
	fileCPF = fopen(pathCPF, "r");

	if(fileCPF == NULL) {
		printf("Erro ao abrir arquivo de entrada\n");
		return;
	} else {
		while(!feof(fileCPF)) {
			result = fgets(linha, 100, fileCPF);

			if(result) {
				n = atoi(linha);
				cpf[cont++] = n;
			}
		}
	}

	cont = 0;
	if(file == NULL) {
		printf("Erro ao abrir arquivo de entrada\n");
		return;
	} else {
		while(!feof(file)) {
			result = fgets(linha, 100, file);

			if(result) {
				tokenizar(linha);

				n = get_randomIdade();
				sprintf(text, "%d", n);

				strcat(linha, ",");
				strcat(linha, text);

				sprintf(text, "%d", cpf[cont++]);

				strcat(text, ",");
				strcat(text, linha);
				strcat(text, "\n");

				fputs(text, fileClientes);
			}
		}
		printf("cont: %d\n", cont);
	}
	fclose(file);
	fclose(fileClientes);
	fclose(fileCPF);
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

// /**
//  * @brief Realiza a leitura de um arquivo e faz a pesquisa
//  * 
//  * @param raizS ponteiro da arvore simples
//  * @param raizAVL ponteiro da arvore AVL
//  * @param raizRB ponteiro da arvore red black
//  * @param tam valor do arquivo de entrada a ser aberto
//  * @param tS ponteiro para o tempo da arvore simples
//  * @param tAVL ponteiro para o tempo da arvore AVL
//  * @param tRB ponteiro para o tempo da arvore rubro negra
//  */
// void readFileSearch(TreeS **raizS, TreeAVL **raizAVL, TreeRB **raizRB, int tam, double *tS, double *tAVL, double *tRB) {
// 	FILE *fileS, *fileAVL, *fileRB;
// 	TreeS *aux1;
// 	TreeAVL *aux2;

// 	clock_t time;

// 	char linha[100];
// 	char text[20];
// 	char *result;

// 	int cont;
// 	double quantS, quantAVL, quantRB;

// 	cont = quantS = quantAVL = quantRB = 0;
	
// 	sprintf(text, "%d", tam);
// 	strcpy(linha, PATH_SEARCH);
// 	strcat(linha, strcat(text, ".txt"));

// 	fileS = fopen(linha, "r");
// 	fileAVL = fopen(linha, "r");
// 	fileRB = fopen(linha, "r");

// 	if(fileS == NULL) {
// 		printf("Erro ao abrir arquivo de pesquisa\n");
// 		return;
// 	} else {
// 		Record r;
		
// 		time = clock();

// 		while(!feof(fileS)) {
// 			result = fgets(linha, 100, fileS);

// 			if(result) {
// 				r.key = atof(linha);
// 				pesquisaS(raizS, &aux1, r, &quantS);
// 				cont++;
// 			}
// 		}
// 		*tS = ((clock() - time) / (double)CLOCKS_PER_SEC); // 1

// 		time = clock();

// 		while(!feof(fileAVL)) {
// 			result = fgets(linha, 100, fileAVL);

// 			if(result) {
// 				r.key = atof(linha);
// 				pesquisaAVL(raizAVL, &aux2, r, &quantAVL);
// 				cont++;
// 			}
// 		}
// 		*tAVL = ((clock() - time) / (double)CLOCKS_PER_SEC); // 2

// 		time = clock();

// 		while(!feof(fileRB)) {
// 			result = fgets(linha, 100, fileRB);

// 			if(result) {
// 				r.key = atof(linha);
// 				searchRB(*raizRB, r, &quantRB);
// 				cont++;
// 			}
// 		}
// 		*tRB = ((clock() - time) / (double)CLOCKS_PER_SEC); // 3
// 	}
// 	fclose(fileS);
// 	fclose(fileAVL);
// 	fclose(fileRB);
	
// 	printf("\n%d valores pesquisados\n\n", cont);
// 	printf("(%.0lf) pesquisas realizadas arvore Simples\n", quantS);
// 	printf("(%.0lf) pesquisas realizadas arvore AVL\n", quantAVL);
// 	printf("(%.0lf) pesquisas realizadas arvore RB\n", quantRB);
// }

// /**
//  * @brief Realiza a leitura de um arquivo de 1000000000 de entradas
//  * este metodo nao deve ser utilizado, consome muito recurso
//  * 
//  * @param raizRB ponteiro da arvore red black
//  * @param tempo ponteiro para o tempo de insercao
//  */
// void readFileInput1Bilhao(TreeRB **raizRB, double *tempo) {
// 	FILE *file, *newFile;

// 	clock_t time;

// 	char linha[100];
// 	char text[20];
// 	char *result;

// 	int cont = 0, contadorRP = 0;

// 	sprintf(text, "%d", 1000000000);
// 	strcpy(linha, PATH_INPUT);
// 	strcat(linha, strcat(text, ".txt"));

// 	file = fopen(linha, "r");
// 	newFile = fopen("src/files/saida.txt", "w");

// 	if(file == NULL) {
// 		printf("Erro ao abrir arquivo de entrada\n");
// 		return;
// 	} else {
// 		Record r;
// 		time = clock();

// 		while(!feof(file)) {
// 			result = fgets(linha, 100, file);

// 			if(result) {
// 				r.key = atof(linha);
// 				insertItemRBCorrecao(raizRB, r, &contadorRP, &cont);

// 				sprintf(linha, "%.6lf", r.key);
// 				strcat(linha, "\n");
// 				fputs(linha, newFile);
// 			}
// 		}
// 		*tempo = ((clock() - time) / (double)CLOCKS_PER_SEC);
// 	}
// 	printf("\n%d valores inseridos no total\n", cont);
// 	printf("\n%d valores repetidos\n", contadorRP);
	
// 	fclose(file);
// }