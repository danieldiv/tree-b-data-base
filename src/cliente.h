#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct Cliente Cliente;

/**
 * Struct utilizado para armazenar o cliente com suas informacoes
 * 
 */
struct Cliente {
    int cpf;
    int idade;
    char *nome;
};

void tokenizarClientes(char *str, Cliente *c, int *aux, int *remover, int *cpf);

#endif