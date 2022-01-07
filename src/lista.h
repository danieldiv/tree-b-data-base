#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item Item;
typedef struct Block Block;
typedef struct Lista Lista;

struct Item {
	char *valor;
	int cpfStart;
	int cpfEnd;
};

struct Block {
	Item dado;
	Block *prox;
};

struct Lista {
	Block *first;
	Block *last;
};

void FLVazia(Lista *l);
void LInsere(Lista *l, Item d);
void Limprime(Lista *l);

#endif