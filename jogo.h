#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>

// Estrutura para representar o tabuleiro
typedef struct {
    int linhas;
    int colunas;
    char **matriz;
} Matriz;

// Funções principais
Matriz criar_Matriz(int linhas, int colunas);
void limpar_Matriz(Matriz *a);
Matriz ler_ficheiro(const char *nome_Ficheiro);
void imprimir_Matriz(Matriz a);
void maiuscula_Elem(Matriz a, char x, int y);
void riscar_Elem(Matriz a, char x, int y);

#endif // JOGO_H
