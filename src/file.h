#ifndef FILE_H
#define FILE_H

#include "lista.h"
#include "btree.h"

#define PATH_CLIENTES "src/files/clientes/"

#define TRUE 1
#define FALSE 0

void writeFile(int start, int end, char *valor);
void readFileConcat(Lista *lista);
void readFileIntervalo(Pagina **p);

void tokenizar(char *str);

int get_random();
int get_randomIdade();

#endif