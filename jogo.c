#include <stdio.h>
#include <stdlib.h>
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


    if(linha >= 0 && linha< a.linhas && coluna >= 0 && coluna < a.colunas){
        a.matriz[linha][coluna] = a.matriz[linha][coluna] - 32; // mete em maiucula
    }else{
        printf("\n\nA coordenada (%c, %d) nao esta dentro da matriz\n\n", x, y);
    }
    //a.matriz[y-1][x-'a'] = a.matriz[y-1][x-'a'] - 32; // -32 serve para por em maiuscula pela tabela ASCII
}



void riscar_Elem (Matriz a, char x, int y) {
    int linha = y-1;
    int coluna = x-'a';

    if(linha >= 0 && linha < a.linhas && coluna >= 0 && coluna < a.colunas){
        a.matriz[linha][coluna] = '#';
    }else{
        printf("\n\nA coordenada (%c, %d) nao esta dentro da matriz\n\n", x, y);
    }



    //a.matriz[y-1][x-'a'] = '#'; 

}


#ifndef TESTING

int main (){
    char c, x;
    int y;
    Matriz mapa = {0, 0, NULL};

    while (1) {   
        int i = 0;
        if (scanf(" %c", &c) != 1) printf ("Erro1");
        if (c == 'l') {
            char nome_Ficheiro[100];
            if (scanf ("%s", nome_Ficheiro) != 1) printf ("Erro2");
            limpar_Matriz (&mapa);
            mapa = ler_ficheiro (nome_Ficheiro);
        }
        else if (c == 'b') {
            if (scanf (" %c %d", &x, &y) != 2) printf ("Erro3");
            maiuscula_Elem (mapa, x, y);
        }
        else if (c == 'r') {
            if (scanf (" %c %d", &x, &y) != 2) printf ("Erro4");
            riscar_Elem (mapa, x, y);
        }
        else if (c == 's') {
        break;
        }
        imprimir_Matriz (mapa);
    }
    limpar_Matriz (&mapa);

    return 0;
}
#endif


// teste