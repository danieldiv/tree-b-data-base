#ifndef FILE_H
#define FILE_H

#include "lista.h"
#include "btree.h"
#include "cliente.h"

#define PATH_CLIENTES "src/files/clientes/"

void writeFile(int start, int end, char *valor);

void readFileConcat(Lista *lista);
void readFileIntervalo(Pagina **p);
void readFileClientes(Record *r, Cliente *c, int *aux, char *clientes, char *nome, int valorInsert);

void tokenizar(char *str);

int get_random();
int get_randomIdade();
int get_quantClientes(char *arquivo);

#endif