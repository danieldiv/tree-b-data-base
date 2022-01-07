#include "file.h"

void createFile(Lista *l);
void teste(int a, int b, char *valor);

int main() {

	Item item;

	Lista l;
	FLVazia(&l);

    readFileConcat(&l);
    createFile(&l);
	// Limprime(&l);

    return EXIT_SUCCESS;
}

void createFile(Lista *l) {
    Block *aux;
    char str[20];

	aux = l->first->prox;
	while(aux != NULL) {
        writeFile(aux->dado.cpfStart, aux->dado.cpfEnd, aux->dado.valor);
        // teste(aux->dado.cpfStart, aux->dado.cpfEnd, aux->dado.valor);
		// printf("%d...%d\n%s\n", aux->dado.cpfStart, aux->dado.cpfEnd, aux->dado.valor);
		aux = aux->prox;
	}
}

void teste(int a, int b, char *valor) {
    printf("%d-", a);
    printf("%d\n%s\n", b, valor);
}