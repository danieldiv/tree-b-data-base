#include "file.h"

void createFile(Lista *l);

int main() {

	Pagina *p;
	Record r;

	p = CreateBTree();
	

	readFileIntervalo(&p);
	// Imprime(&p, 0);

	for(int i=8136; i <= 8195; i++) {
		r.key = i;
		Pesquisa(p, &r);
	}
	// printf("r: %d\n", r.key);

	
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