#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"


Matriz criar_Matriz (int linhas, int colunas) {
    Matriz a;
    int i;
    a.linhas = linhas;
    a.colunas = colunas;

    a.matriz = (char **)malloc (linhas * sizeof (char*));
    for (i = 0; i < linhas; i++) {
        a.matriz[i] = (char *) malloc (colunas * sizeof (char));
    }
    return a;
}

void limpar_Matriz (Matriz *a) {
    int i;
    if (a->matriz != NULL) {
        for (i = 0; i < a->linhas; i++) {
            free (a->matriz[i]);
        }
        free (a->matriz);
        a->matriz = NULL;
    }
    a->linhas = 0;
    a->colunas = 0;
}

Matriz ler_ficheiro (const char *nome_Ficheiro) {
    int linhas, colunas, i, j;
    Matriz a;
    FILE *f = fopen (nome_Ficheiro, "r");
    if (f==NULL) {
        printf ( "Erro ao abrir o ficheiro '%s'\n", nome_Ficheiro);
        exit (1);
    }

    if (fscanf (f, " %d %d", &linhas, &colunas) != 2) printf ("Erro5");

    a = criar_Matriz (linhas, colunas);

    for (i = 0;i < linhas; i++) {
        for (j = 0; j< colunas; j++) {
            if (fscanf (f, " %c", &a.matriz[i][j]) != 1) printf ("Erro6");
        }
    }
    return a;
}


void imprimir_Matriz (Matriz a) {
    int i, j;
    for (i=0 ; i < a.linhas; i++) {
        for (j=0; j < a.colunas; j++) {
            printf("%c ", a.matriz[i][j]);
        }
        printf("\n");
    }
}

void maiuscula_Elem (Matriz a, char x, int y) {
    int linha = y - 1;
    int coluna = x - 'a';

    if (linha >= 0 && linha< a.linhas && coluna >= 0 && coluna < a.colunas) {
        a.matriz[linha][coluna] = a.matriz[linha][coluna] - 32; // mete em maiucula
    }
    else {
        printf("\n\nA coordenada (%c, %d) nao esta dentro da matriz\n\n", x, y);
    }
    //a.matriz[y-1][x-'a'] = a.matriz[y-1][x-'a'] - 32; // -32 serve para por em maiuscula pela tabela ASCII
}



void riscar_Elem (Matriz a, char x, int y) {
    int linha = y-1;
    int coluna = x-'a';

    if (linha >= 0 && linha < a.linhas && coluna >= 0 && coluna < a.colunas) {
        a.matriz[linha][coluna] = '#';
    }
    else {
        printf("\n\nA coordenada (%c, %d) nao esta dentro da matriz\n\n", x, y);
    }
}

int ehMaiuscula (char a) {
    if (a >= 65 && a <= 90) {
        return 1;
    }
    else return 0;
}

int verificarLetrasRiscadas(Matriz *a) {
    int i, j, r = 1;
    printf("Coordenadas que não cumprem a regra Riscadas: ");
    for (i = 0; i < a->linhas; i++) {// Como o C é "lazy" podemos colocar o i>0 antes que assim ele já não faz a parte de acessar fora da memoria 
        for (j = 0; j < a->colunas; j++) {
            if (a->matriz[i][j] == '#') {
                // Verifica as células adjacentes com verificações de limites
                if ((i > 0 && a->matriz[i-1][j] == '#') ||       // Célula acima
                    (i < a->linhas - 1 && a->matriz[i+1][j] == '#') || // Célula abaixo
                    (j > 0 && a->matriz[i][j-1] == '#') ||       // Célula à esquerda
                    (j < a->colunas - 1 && a->matriz[i][j+1] == '#')) { // Célula à direita
                    r = 0;
                    printf("%c%d ", j+97, i+1);
                }
            }
        }
    }
    printf("\n");
    return r;
}

int verificarLetrasRiscadasComMaiusculas (Matriz *a) {
    int i, j, r = 1;
    printf("Coordenadas que não cumprem a regra Riscadas e Maiúsculas: ");
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (a->matriz[i][j] == '#') {// Como o C é "lazy" podemos colocar o i>0 antes que assim ele já não faz a parte de acessar fora da memoria 
                // Verifica as células adjacentes com verificações de limites
                if ((i > 0 && !ehMaiuscula(a->matriz[i-1][j])) ||       // Célula acima
                    (i < a->linhas - 1 && !ehMaiuscula(a->matriz[i+1][j])) || // Célula abaixo
                    (j > 0 && !ehMaiuscula(a->matriz[i][j-1])) ||       // Célula à esquerda
                    (j < a->colunas - 1 && !ehMaiuscula (a->matriz[i][j+1]))) { // Célula à direita
                    r = 0;
                    printf("%c%d ", j+97, i+1);
                }
            }
        }
    }
    printf("\n");
    return r;
}


int verificarLetrasMaiusculasRepetidas (Matriz *a) {
    int i, j, r = 1, t;
    // Verifica linhas.
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (ehMaiuscula (a->matriz[i][j])) {
                for (t = j + 1;t < a->colunas; t++) {
                    if (a->matriz[i][j] == a->matriz[i][t]) {
                        r = 0;
                        printf ("A coordenada %c%d não cumpre a regra das Maiusculas.\n",j+97, i+1);
                        break;
                    }
                }
            }
        }
    }
    return r;
}


void iniciarPilha (Pilha *a) {
    a->topo = NULL;
}

void colocarMatrizNaPilha (Pilha *a, Matriz estadoDoJogo) {
    int i, j;
    Node *c = malloc (sizeof (Node));
    c->estado.linhas = estadoDoJogo.linhas;
    c->estado.colunas = estadoDoJogo.colunas;

    c->estado.matriz = malloc (estadoDoJogo.colunas * sizeof(char*)); // Aloca memória para a matriz
    // Faz uma cópia da Matriz
    for (i = 0; i < estadoDoJogo.linhas; i++) { 
        c->estado.matriz[i] = malloc (estadoDoJogo.colunas * (sizeof (char)));
        for (j = 0; j < estadoDoJogo.colunas; j++) {
            c->estado.matriz[i][j] = estadoDoJogo.matriz[i][j];
        }
    }
    c->proximo = a->topo;
    a->topo = c;
}

void retirarMatrizDaPilha (Pilha *a) {
    if (a->topo == NULL) {
        printf("A pilha está vazia. Não há nenhuma Matriz para retirar.\n");
    }
        // Obtém o nó do topo
    Node *c = a->topo;
    a->topo = c->proximo;

    // Liberta a memória da matriz no nó
    limpar_Matriz (&(c->estado));

    // Liberta o nó
    free (c);
}

void restoraMatrizParaAUltimaJogada (Pilha *a, Matriz *atual) {
    int i, j;
    atual->linhas = a->topo->estado.linhas;
    atual->colunas = a->topo->estado.colunas;
    for (i = 0; i < atual->linhas; i++) {
        for (j = 0; j < atual->colunas; j++) {
            atual->matriz[i][j] = a->topo->estado.matriz[i][j];
        }
    }
}

void limpar_Pilha (Pilha *a) {
    while (a->topo != NULL) {
        // Obtém o nó do topo
        Node *c = a->topo;
        a->topo = c->proximo;

        // Libera a memória da matriz no nó
        for (int i = 0; i < c->estado.linhas; i++) {
            free(c->estado.matriz[i]);
        }
        free(c->estado.matriz);

        // Libera o nó
        free(c);
    }
}


#ifndef TESTING

int main (){
    char c, x;
    int y;
    Matriz mapa = {0, 0, NULL};
    Pilha jogadas;
    iniciarPilha (&jogadas);

//  Simula o comando "l j1.txt" para poupar tempo durante o desenvolvimento
//    mapa = ler_ficheiro("Teste de Maiusculas.txt");
//    imprimir_Matriz (mapa);
//    colocarMatrizNaPilha (&jogadas, mapa);

    while (1) {   
        if (scanf(" %c", &c) != 1) printf ("Erro1");
        if (c == 'l') {
            char nome_Ficheiro[100];
            if (scanf ("%s", nome_Ficheiro) != 1) printf ("Erro2");
            limpar_Matriz (&mapa);
            mapa = ler_ficheiro (nome_Ficheiro);
            colocarMatrizNaPilha (&jogadas, mapa);
        }
        else if (c == 'b') {
            if (scanf (" %c %d", &x, &y) != 2) printf ("Erro3");
            maiuscula_Elem (mapa, x, y);
            colocarMatrizNaPilha (&jogadas, mapa);
        }
        else if (c == 'r') {
            if (scanf (" %c %d", &x, &y) != 2) printf ("Erro4");
            riscar_Elem (mapa, x, y);
            colocarMatrizNaPilha (&jogadas, mapa);
        }
        else if (c == 's') {
        break;
        }
        else if (c == 'd') {
            if (jogadas.topo->proximo == NULL) printf ("Não é possível recuar mais jogadas.\n");
            else {
                retirarMatrizDaPilha (&jogadas);
                restoraMatrizParaAUltimaJogada (&jogadas, &mapa);
            }
        }
        else if (c == 'v') {
            verificarLetrasRiscadas (&mapa);
            verificarLetrasMaiusculasRepetidas (&mapa);
            verificarLetrasRiscadasComMaiusculas (&mapa);
            }
        imprimir_Matriz (mapa);
}
    limpar_Pilha (&jogadas);
    limpar_Matriz (&mapa);

    return 0;
}
#endif
