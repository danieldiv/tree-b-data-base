#include "cliente.h"

/**
 * @brief tokenizarClientes: utilizada para quebrar a string que possui virgulas ( , )
 * 
 * Este metodo e utilizado pelo metodo readFileClientes quando le o arquivo de clientes
 * 
 * @param str valor que sera tokenizado
 * @param c ponteiro referente ao cliente com suas informacoes
 * @param aux utilizado para verificar se encontrou o cpf procurado
 * @param remover controle utilizado para saber se encontrou o cpf para remover
 * @param cpf utilizado para comparar quando insere um novo cliente
 */
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