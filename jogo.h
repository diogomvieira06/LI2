#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>

// Estrutura para representar o tabuleiro
typedef struct {
    int linhas;
    int colunas;
    char **matriz;
} Matriz;

// Estrutura de pilha para, poder reverter jogadas
typedef struct Node { // Tem struct Node para poder ser chamada recursivamente
    Matriz estado;
    struct Node *proximo;
} Node;

typedef struct {
    Node *topo;
} Pilha;


// Funções principais
Matriz criar_Matriz(int linhas, int colunas);
void limpar_Matriz(Matriz *a);
Matriz ler_ficheiro(const char *nome_Ficheiro);
void imprimir_Matriz(Matriz a);
void maiuscula_Elem(Matriz a, char x, int y);
void riscar_Elem(Matriz a, char x, int y);
int ehMaiuscula (char a);
int verificarLetrasRiscadas(Matriz *a);
void imprimirLetrasRiscadas (Matriz *a);
int verificarLetrasRiscadasComMaiusculas (Matriz *a);
void imprimirLetrasRiscadasComMaiusculas (Matriz *a);
int verificarLetrasMaiusculasRepetidasLinha(Matriz *a);
void imprimirLetrasMaiusculasRepetidasLinha(Matriz *a);
int verificarLetrasMaiusculasRepetidasColuna(Matriz *a);
void imprimirLetrasMaiusculasRepetidasColuna(Matriz *a);
void iniciarPilha (Pilha *a);
void colocarMatrizNaPilha (Pilha *a, Matriz estadoDoJogo);
void retirarMatrizDaPilha (Pilha *a);
void restoraMatrizParaAUltimaJogada (Pilha *a, Matriz *atual);
void limpar_Pilha (Pilha *a);
void gravar_ficheiro(Matriz a, const char *nome_Ficheiro);




#endif // JOGO_H