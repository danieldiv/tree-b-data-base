#include "cliente.h"

void tokenizarClientes(char *str, Cliente *c, int *aux, int *remover, int *cpf) {
	const char sep[] = ",";
	char *tokens;

	int controle = 0;
	
	tokens = strtok(str, sep);
	
	while(tokens != NULL) {
		if(controle == 0) {
			*cpf = atoi(tokens);

			if(*cpf != c->cpf) {
				*aux = FALSE;
				return;
			}
			*remover = FALSE;
			*aux = TRUE;
		} else if(controle == 1) {
			strcpy(c->nome, tokens);
		} else if(controle == 2) {
			c->idade = atoi(tokens);
		}
		controle++;
		tokens = strtok(NULL, sep);
	}
}