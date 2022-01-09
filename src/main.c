#include "file.h"

#include <sys/stat.h>
#include <unistd.h>

#define DIRETORIO "./teste"

void createFile(Lista *l);
int menu();

int main() {

	Lista l;
	FLVazia(&l);

	readFileConcat(&l);
	createFile(&l);

	//========================

	FILE *file;
	char *path = (char*)malloc(50 * sizeof(char));

	char *result, linha[100], text[10];
	// Record r;
	// int aux = TRUE;

	

	// =========================

	Pagina *p;
	Record r;
	Cliente c;

	int aux;
	int valor;

	p = CreateBTree();

	int op;

	do {
		system("clear");
        op = menu();
		printf("\n");
		
		switch(op) {
			case 1:
				if(p == NULL) {
					readFileIntervalo(&p);
					printf("Os valores dos CPFs foram carregados na arvore, com o seu limite e nome do arquivo.\n");
				} else
					printf("A arvore B ja possui valores pre-carregados!\n");
			break;
			case 2:
				if(p == NULL)
					printf("Arvore B vazia!\n");
				else {
					printf("Informe o valor do CPF para pesquisar: ");
					scanf("%d", &valor);

					r.key = valor;
					Pesquisa(p, &r);

					if(!(r.key == -1)) {
						c.cpf = valor;
						aux = FALSE;

						readFileClientes(r, &c, &aux);

						if(aux) {
							printf("Cliente: %s\n", c.nome);
							printf("Idade: %d\n", c.idade);
							printf("CPF: %d\n", c.cpf);
						} else {
							printf("O cpf (%d) nao foi encontrado na lista de clientes!\n", c.cpf);
						}
					}
				}
			break;
			// case 3:
				// remove("src/files/teste.txt");
				// remove("src/files/clientes/1016...1084.txt");
			// break;
			case 3:
				if(p == NULL)
					printf("Arvore B vazia!\n");
				else {
					printf("Informe o valor do CPF para remover: ");
					scanf("%d", &valor);

					r.key = valor;
					Pesquisa(p, &r);

					if(!(r.key == -1)) {
						c.cpf = valor;
						aux = FALSE;

						readFileClientes(r, &c, &aux);

						if(aux) {
							printf("Cliente: %s\n", c.nome);
							printf("Idade: %d\n", c.idade);
							printf("CPF: %d\n", c.cpf);
						} else {
							printf("O cpf (%d) nao foi encontrado na lista de clientes!\n", c.cpf);
						}
					}
				}
				// strcpy(path, "src/files/teste.txt");

				// file = fopen(path, "w");

				// if(file == NULL) {
				// 	printf("Nao foi possivel abrir o arquivo teste.txt\n");
				// 	// return;
				// } 
				// else {
				// 	while(!feof(file)) {
				// 		result = fgets(linha, sizeof(linha), file);
				// 		printf("teste\n");
				// 		if(result) {
				// 			printf("teste\n");
				// 		} else {
				// 			break;
				// 		}
				// 	}
				// }

				// fclose(file);
				// free(path);
			break;
			case 0:
				printf("O programa sera finalizado!\n");
				return EXIT_SUCCESS;
			default:
				printf("Opcao invalida!\n");
		}
		system("read -p \"\nPressione enter para continuar...\" continue");
		
	} while (op != 0);

    return EXIT_SUCCESS;
}


/**
 * @brief Menu de opcoes principal
 * 
 */
int menu() {
	int op;

	printf("====================\n");
	printf("   MENU DE OPCOES\n");
	printf("====================\n\n");

	printf("1 - Incializar arvore\n");
	printf("2 - Pesquisar Cliente\n");
	printf("3 - Remover Cliente\n");
	printf("0 - Sair\n\n");

	printf("Escolha uma opção: ");
	scanf("%d", &op);

	return op;
}

void createFile(Lista *l) {
    Block *aux;
    char str[20];

	aux = l->first->prox;
	while(aux != NULL) {
        writeFile(aux->dado.cpfStart, aux->dado.cpfEnd, aux->dado.valor);
		aux = aux->prox;
	}
}