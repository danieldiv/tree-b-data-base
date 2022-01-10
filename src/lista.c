#include "lista.h"

void FLVazia(Lista *l) {
	l->first = (Block *) malloc(sizeof(Block));
	l->last = l->first;
	l->first->prox = NULL;
}

void LInsere(Lista *l, Item d) {
	l->last->prox = (Block *) malloc(sizeof(Block));
	l->last = l->last->prox;
	l->last->dado = d;
	l->last->prox = NULL;
}

void Limprime(Lista *l) {
	Block *aux;

	aux = l->first->prox;
	while(aux != NULL) {
		// printf("%d...%d\n%s\n", aux->dado.cpfStart, aux->dado.cpfEnd, aux->dado.valor);
		printf("%s", aux->dado.valor);
		aux = aux->prox;
	}
}