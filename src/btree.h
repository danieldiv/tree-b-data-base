#ifndef BTREE_H 
#define BTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define M 1
#define MM (M * 2 + 1)

#define FALSE 0
#define TRUE  1

typedef struct Record Record;
typedef struct Pagina Pagina;

struct Record {
  int key;
  int limite;
  char *arquivo;
};

struct Pagina {
  short n;
  Record r[MM];
  Pagina *p[MM + 1];
};


Pagina* CreateBTree();

void Pesquisa(Pagina *p, Record *r);
void InsereNaPagina(Pagina *p, Pagina *pdir, Record r);
void InsertFixUp(Pagina **p, Pagina **pr, Record r, Record *rr, short *Overflow);
void Insere(Pagina **p, Record r);

void RemoveFixUp(Pagina *p, Pagina *pai, int PosPai, int *underflow);
void Antecessor(Pagina *p, int i, Pagina *pai, int *underflow);
void Remove(Pagina **p, int key, int *underflow);
void Retira(Pagina **p, int key);

void Imprime(Pagina **p, int level);

#endif
