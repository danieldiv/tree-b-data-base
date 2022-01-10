#ifndef FILE_H
#define FILE_H

#include "lista.h"
#include "btree.h"

#define PATH_CLIENTES "src/files/clientes/"

#define TRUE 1
#define FALSE 0

typedef struct Cliente Cliente;

struct Cliente {
    int cpf;
    int idade;
    char *nome;
};

void writeFile(int start, int end, char *valor);

void readFileConcat(Lista *lista);
void readFileIntervalo(Pagina **p);
void readFileClientes(Record *r, Cliente *c, int *aux, char *clientes);

void tokenizar(char *str);
void tokenizarClientes(char *str, Cliente *c, int *aux, int *remover);

int get_random();
int get_randomIdade();
int get_quantClientes(char *arquivo);

#endif