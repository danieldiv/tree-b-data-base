#include "file.h"

// #include <sys/stat.h>
// #include <unistd.h>

void createFile(Lista *l);
int menu();

int main() {

	Lista l;
	FLVazia(&l);

	readFileConcat(&l);
	createFile(&l);

	char *path = (char*)malloc(50 * sizeof(char));
	char *result;
	char *nome;

	Pagina *p;
	Record r;
	Cliente c;

	int aux;
	int valor;
	int op;

	p = CreateBTree();

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
						if(get_quantClientes(r.arquivo) == 0)
							printf("O arquivo %s nao possui clientes cadastrados!\n", r.arquivo);
						else {
							c.cpf = valor;
							aux = FALSE;

							result = (char*)malloc(200*sizeof(char));
							nome = (char*)malloc(sizeof(char));
							strcpy(nome, "");
							
							readFileClientes(&r, &c, &aux, result, nome, -1);

							if(aux) {
								printf("Cliente: %s\n", c.nome);
								printf("Idade: %d\n", c.idade);
								printf("CPF: %d\n", c.cpf);
							} else {
								printf("O cpf (%d) nao foi encontrado na lista de clientes!\n", c.cpf);
							}
						}
					}
				}
			break;
			case 3:
				if(p == NULL)
					printf("Arvore B vazia!\n");
				else {
					printf("Informe o valor do CPF para remover: ");
					scanf("%d", &valor);

					r.key = valor;
					Pesquisa(p, &r);

					if(!(r.key == -1)) {
						if(get_quantClientes(r.arquivo) == 0)
							printf("O arquivo %s nao possui clientes cadastrados!\n", r.arquivo);
						else {
							c.cpf = valor;
							aux = FALSE;

							result = (char*)malloc(200*sizeof(char));
							nome = (char*)malloc(sizeof(char));
							strcpy(nome, "");

							readFileClientes(&r, &c, &aux, result, nome, -1);

							sprintf(path, "src/files/clientes/%d...%d.txt", r.key, r.limite);
							remove(path);

							writeFile(r.key, r.limite, result);
							r.quant = get_quantClientes(r.arquivo);

							if(aux) {
								printf("Cliente: %s\n", c.nome);
								printf("Idade: %d\n", c.idade);
								printf("CPF: %d\n", c.cpf);
								printf("\nO cliente com as informacoes acima foi excluido!\n");
								printf("A quantidade de clientes dentro do arquivo (%s.txt) foi reduzido para: %d\n", r.arquivo, r.quant);
							} else {
								printf("O cpf (%d) nao foi encontrado na lista de clientes!\n", c.cpf);
							}
						}
					}
				}
			break;
			case 4:
				if(p == NULL)
					printf("Arvore B vazia!\n");
				else {
					printf("Informe o valor do CPF para inserir: ");
					scanf("%d", &valor);
					fflush(stdin);

					r.key = valor;
					Pesquisa(p, &r);

					if(!(r.key == -1)) {
						if(get_quantClientes(r.arquivo) == 10)
							printf("O arquivo (%s.txt) atingiu o limite maximo de clientes cadastrados!\n", r.arquivo);
						else {
							nome = (char*)malloc(20 * sizeof(char));
							sprintf(nome, "%d,Nome%d,%d\n", valor, get_randomIdade(), get_randomIdade());


							c.cpf = valor;
							aux = FALSE;

							result = (char*)malloc(200*sizeof(char));
							readFileClientes(&r, &c, &aux, result, nome, valor);

							sprintf(path, "src/files/clientes/%d...%d.txt", r.key, r.limite);
							remove(path);

							writeFile(r.key, r.limite, result);
							r.quant = get_quantClientes(r.arquivo);

							if(!aux) {
								printf("O cpf (%d) foi adicionado na lista de clientes!\n", c.cpf);
								printf("A quantidade de clientes dentro do arquivo (%s.txt) foi aumentado para: %d\n", r.arquivo, r.quant);
							} else {
								printf("O cpf (%d) ja existe na lista de clientes!\n", c.cpf);
							}
						}
					}
				}
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
	printf("4 - Inserir Cliente\n");
	printf("0 - Sair\n\n");

	printf("Escolha uma opção: ");
	scanf("%d", &op);

	return op;
}

void createFile(Lista *l) {
    Block *aux;

	aux = l->first->prox;
	while(aux != NULL) {
        writeFile(aux->dado.cpfStart, aux->dado.cpfEnd, aux->dado.valor);
		aux = aux->prox;
	}
}