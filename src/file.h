#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define PATH_INPUT "src/files/input"
#define PATH_SEARCH "src/files/search"

#define TRUE 1
#define FALSE 0

void writeFile(char *nome, char *valor);
void readFileConcat();
void tokenizar(char *str);
// void readFileSearch(TreeS **raizS, TreeAVL **raizAVL, TreeRB **raizRB, int tam, double *tS, double *tAVL, double *tRB);
void randomValue();

// void readFileInput1Bilhao(TreeRB **raizRB, double *tempo);

int get_random();
int get_randomIdade();

#endif