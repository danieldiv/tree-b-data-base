#include "file.h"

void createFile(Lista *l);

int main() {

	Pagina *p;
	Record r;
	Cliente c;

	int aux;
	int valor;
	
	// valor = 8930;
	// valor = 8873;
	// valor = 8882;
	valor = 8931;

	p = CreateBTree();
	

	readFileIntervalo(&p);
	// Imprime(&p, 0);

	// for(valor=8873; valor <= 8930; valor++) {
		r.key = valor;
		Pesquisa(p, &r);

		if(!(r.key == -1)) {
			c.cpf = valor;
			aux = FALSE;

			readFileClientes(r, &c, &aux);

			if(aux) {
				printf("\nCliente: %s\n", c.nome);
				printf("Idade: %d\n", c.idade);
				printf("CPF: %d\n\n", c.cpf);
			} else {
				printf("O cpf (%d) nao foi encontrado na lista de clientes!\n", c.cpf);
			}
		}
	// }

	
	// Item item;

	// Lista l;
	// FLVazia(&l);

    // readFileConcat(&l);
    // createFile(&l);
	// Limprime(&l);

    return EXIT_SUCCESS;
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