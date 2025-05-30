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

typedef struct {
    int linha, coluna;
} Posicao;


// Funções principais
Matriz criar_Matriz(int linhas, int colunas);
void limpar_Matriz(Matriz *a);
Matriz ler_ficheiro(const char *nome_Ficheiro);
void imprimir_Matriz(Matriz a);
void imprimir_Matriz_Ponteiro (Matriz *a, int ultima_linha, int ultima_coluna);
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
Matriz cria_Matriz_copia (Matriz *a);
int verCaminho(Matriz *a, int linha1, int coluna1, int linha2, int coluna2);
int verCaminhoMatriz (Matriz *a);
int verCaminhoMaiusculas (Matriz *a);
void imprimirVerCaminhoMaiusculas(Matriz *a);
void risca_Minusculas_Repetidas (Matriz *a);
void coloca_Em_Maiuscula_Pela_Riscada (Matriz *a);
int ehMinuscula (char a);
void coloca_Em_Maiuscula_Pelo_Caminho (Matriz *a);
int quant_Minusculas (Matriz *a);
int verificar_Minusculas_Repetidas_com_Maiusculas (Matriz *a);
void risca_Rodeada_Maiusculas (Matriz *a);
Matriz cria_Matriz_igual (Matriz *a);

#endif // JOGO_H