#include "file.h"

int main() {

    char *nome = (char*)malloc(100*sizeof(char));
    char *valor = (char*)malloc(100*sizeof(char));

    // readFileConcat();

    strcpy(valor, "testando");

    strcpy(nome, "src/files/clientes/");
	strcat(nome, strcat(nome, "teste.txt"));

    writeFile(nome, valor);

    return EXIT_SUCCESS;
}