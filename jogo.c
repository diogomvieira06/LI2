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
/*
void imprimir_Matriz_Ponteiro (Matriz *a) {
    int i, j;
    for (i=0 ; i < a->linhas; i++) {
        for (j=0; j < a->colunas; j++) {
            printf("%c ", a->matriz[i][j]);
        }
        printf("\n");
    }
}
*/

void imprimir_Matriz_Ponteiro (Matriz *a, int ultima_linha, int ultima_coluna) {
    for (int i = 0; i < a->linhas; i++) {
        for (int j = 0; j < a->colunas; j++) {
            if (i == ultima_linha && j == ultima_coluna)
                printf("\033[93m%c \033[0m", a->matriz[i][j]);  // Amarelo
            else
                printf("%c ", a->matriz[i][j]);
        }
        printf("\n");
    }
}

void maiuscula_Elem (Matriz a, char x, int y) {
    int linha = y - 1;
    int coluna = x - 'a';

    if (linha >= 0 && linha < a.linhas && coluna >= 0 && coluna < a.colunas) {
        char atual = a.matriz[linha][coluna];
        if (atual >= 'a' && atual <= 'z') {
            a.matriz[linha][coluna] = atual - 32; // Converte para maiúscula
        } else {
            printf("Não é possível colocar em maiúscula a célula (%c, %d): não é letra minúscula.\n", x, y);
        }
    } else {
        printf("A coordenada (%c, %d) nao está dentro da matriz.\n", x, y);
    }
}




void riscar_Elem (Matriz a, char x, int y) {
    int linha = y - 1;
    int coluna = x - 'a';

    if (linha >= 0 && linha < a.linhas && coluna >= 0 && coluna < a.colunas) {
        if (!ehMaiuscula(a.matriz[linha][coluna])) {
            a.matriz[linha][coluna] = '#';
        } else {
            printf("\n\nNão é possível riscar uma letra maiúscula na coordenada (%c, %d)\n\n", x, y);
        }
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
    for (i = 0; i < a->linhas; i++) {// Como o C é "lazy" podemos colocar o i>0 antes que assim ele já não faz a parte de acessar fora da memoria 
        for (j = 0; j < a->colunas; j++) {
            if (a->matriz[i][j] == '#') {
                // Verifica as células adjacentes com verificações de limites
                if ((i > 0 && a->matriz[i-1][j] == '#') ||       // Célula acima
                    (i < a->linhas - 1 && a->matriz[i+1][j] == '#') || // Célula abaixo
                    (j > 0 && a->matriz[i][j-1] == '#') ||       // Célula à esquerda
                    (j < a->colunas - 1 && a->matriz[i][j+1] == '#')) { // Célula à direita
                    r = 0;
                }
            }
        }
    }
    return r;
}

void imprimirLetrasRiscadas (Matriz *a) {
    int i, j;
    printf("Regra das Riscadas: ");
    for (i = 0; i < a->linhas; i++) {// Como o C é "lazy" podemos colocar o i>0 antes que assim ele já não faz a parte de acessar fora da memoria 
        for (j = 0; j < a->colunas; j++) {
            if (a->matriz[i][j] == '#') {
                // Verifica as células adjacentes com verificações de limites
                if ((i > 0 && a->matriz[i-1][j] == '#') ||       // Célula acima
                    (i < a->linhas - 1 && a->matriz[i+1][j] == '#') || // Célula abaixo
                    (j > 0 && a->matriz[i][j-1] == '#') ||       // Célula à esquerda
                    (j < a->colunas - 1 && a->matriz[i][j+1] == '#')) { // Célula à direita
                    printf("%c %d, ", j+97, i+1);
                }
            }
        }
    }
    printf("\n");
}


int verificarLetrasRiscadasComMaiusculas(Matriz *a) {
    int i, j, r = 1;

    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (a->matriz[i][j] == '#') {
                int cima = (i > 0 && (ehMinuscula(a->matriz[i - 1][j]) || a->matriz[i - 1][j] == '#'));
                int baixo = (i < a->linhas - 1 && (ehMinuscula(a->matriz[i + 1][j]) || a->matriz[i + 1][j] == '#'));
                int esquerda = (j > 0 && (ehMinuscula(a->matriz[i][j - 1]) || a->matriz[i][j - 1] == '#'));
                int direita= (j < a->colunas - 1 && (ehMinuscula(a->matriz[i][j + 1]) || a->matriz[i][j + 1] == '#'));
                // pus assim para ser mais facil de perceber, mas a funçao funciona como estava antes
                if (cima || baixo || esquerda || direita) {
                    r = 0;
                }
            }
        }
    }
    return r;
}

//pus so as variaveis cima, baixo, direita e esquerda para perceber melhor
//a funçao funciona como a anterior
void imprimirLetrasRiscadasComMaiusculas(Matriz *a) {
    int i, j;
    printf("Regra das Maiúsculas à beira das Riscadas: ");

    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (a->matriz[i][j] == '#') {
                int cima     = (i > 0 && !ehMaiuscula(a->matriz[i - 1][j]));
                int baixo    = (i < a->linhas - 1 && !ehMaiuscula(a->matriz[i + 1][j]));
                int esquerda = (j > 0 && !ehMaiuscula(a->matriz[i][j - 1]));
                int direita  = (j < a->colunas - 1 && !ehMaiuscula(a->matriz[i][j + 1]));

                if (cima || baixo || esquerda || direita) {
                    printf("%c %d, ", j + 97, i + 1); 
                }
            }
        }
    }
    printf("\n");
}

int verificarLetrasMaiusculasRepetidasLinha(Matriz *a) {
    int i, j, t, r = 1;
    // Verifica linhas
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (ehMaiuscula(a->matriz[i][j])) {
                for (t = j + 1; t < a->colunas; t++) {
                    if (a->matriz[i][j] == a->matriz[i][t]) {
                        r = 0;
                    }
                }
            }
        }
    }
    return r;
}


void imprimirLetrasMaiusculasRepetidasLinha(Matriz *a) {
    int i, j, t;
    int repetidasNaLinha[a->colunas]; // Array para marcar repetições numa linha;
    printf ("Regra das Maiusculas Repetidas na Linha: ");

    // Verifica linhas
    for (i = 0; i < a->linhas; i++) {
        // Inicializa o array de repetidasNaLinha para a linha atual
        for (j = 0; j < a->colunas; j++) {
            repetidasNaLinha[j] = 0;
        }

        for (j = 0; j < a->colunas; j++) {
            if (ehMaiuscula(a->matriz[i][j]) && !repetidasNaLinha[j]) {
                for (t = j + 1; t < a->colunas; t++) {
                    if (a->matriz[i][j] == a->matriz[i][t]) {
                        // Marca as colunas como repetidas
                        repetidasNaLinha[j] = 1;
                        repetidasNaLinha[t] = 1;
                    }
                }
            }
        }
        for (j = 0; j < a->colunas; j++) {
            // Se a letra foi marcada como repetida, imprime a coordenada
            if (repetidasNaLinha[j]) {
                printf("%c%d ", j + 97, i + 1);
            }
        }
    }
    printf ("\n");
}



int verificarLetrasMaiusculasRepetidasColuna(Matriz *a) {
    int i, j, t, r = 1;
    // Verifica colunas
    for (j = 0; j < a->colunas; j++) {
        for (i = 0; i < a->linhas; i++) {
            if (ehMaiuscula(a->matriz[i][j])) {
                for (t = i + 1; t < a->linhas; t++) {
                    if (a->matriz[i][j] == a->matriz[t][j]) {
                        r = 0;
                    }
                }
            }
        }
    }
    return r;
}

void imprimirLetrasMaiusculasRepetidasColuna(Matriz *a) {
    int i, j, t;
    int repetidasNaColuna[a->linhas]; // Array para marcar repetições numa coluna;
    printf ("Regra das Maiusculas Repetidas na Coluna: ");
    
    // Verifica colunas
    for (j = 0; j < a->colunas; j++) {
        // Inicializa o array de repetidasNaColuna para a Coluna atual
        for (i = 0; i < a->linhas; i++) {
            repetidasNaColuna[i] = 0;
        }

        for (i = 0; i < a->linhas; i++) {
            if (ehMaiuscula(a->matriz[i][j]) && !repetidasNaColuna[i]) {
                for (t = i + 1; t < a->linhas; t++) {
                    if (a->matriz[i][j] == a->matriz[t][j]) {
                        // Marca as linhas como repetidas
                        repetidasNaColuna[i] = 1;
                        repetidasNaColuna[t] = 1;
                    }
                }
            }
        }
        for (i = 0; i < a->linhas; i++) {
            // Se a letra foi marcada como repetida, imprime a coordenada
            if (repetidasNaColuna[i]) {
                printf("%c%d ", j + 97, i + 1);
            }
        }
    }
    printf("\n");
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
        return; // termina o que a funçao esta a fazer e para de executar o resto do codigo
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

void gravar_ficheiro(Matriz a, const char *nome_Ficheiro) {
    FILE *f = fopen(nome_Ficheiro, "w");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro '%s' para gravação.\n", nome_Ficheiro);
        return;
    }

    fprintf(f, "%d %d\n", a.linhas, a.colunas);
    for (int i = 0; i < a.linhas; i++) {
        for (int j = 0; j < a.colunas; j++) {
            fprintf(f, "%c", a.matriz[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Jogo gravado no ficheiro '%s'.\n", nome_Ficheiro);
}


Matriz cria_Matriz_copia (Matriz *a) {
    int i, j;
    Matriz visitado = criar_Matriz(a->linhas, a->colunas);
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (ehMaiuscula(a->matriz[i][j])) visitado.matriz[i][j] = '1';
            else visitado.matriz[i][j] = '0';
        }
    }
    return visitado;
}



int verCaminho(Matriz *a, int linha1, int coluna1, int linha2, int coluna2) {
    if (linha1 == linha2 && coluna1 == coluna2) return 1;

    // Cria uma matriz para marcar as células visitadas
    int visitado[a->linhas][a->colunas];
    for (int i = 0; i < a->linhas; i++) {
        for (int j = 0; j < a->colunas; j++) {
            visitado[i][j] = 0;
        }
    }

    // Fila para BFS
    Posicao fila[a->linhas * a->colunas];
    int inicio = 0, fim = 0;

    // Adiciona a posição inicial à fila
    fila[fim++] = (Posicao){linha1, coluna1};
    visitado[linha1][coluna1] = 1;

    // Direções para cima, baixo, esquerda, direita
    int direcoes[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (inicio < fim) {
        Posicao atual = fila[inicio++];
        int linha = atual.linha;
        int coluna = atual.coluna;

        // Verifica todas as direções
        for (int d = 0; d < 4; d++) {
            int novaLinha = linha + direcoes[d][0];
            int novaColuna = coluna + direcoes[d][1];

            // Verifica se a nova posição está dentro dos limites e não foi visitada
            if (novaLinha >= 0 && novaLinha < a->linhas &&
                novaColuna >= 0 && novaColuna < a->colunas &&
                !visitado[novaLinha][novaColuna] &&
                a->matriz[novaLinha][novaColuna] == '1') {

                // Se chegamos ao destino, retorna 1
                if (novaLinha == linha2 && novaColuna == coluna2) {
                    return 1;
                }

                // Marca como visitado e adiciona à fila
                visitado[novaLinha][novaColuna] = 1;
                fila[fim++] = (Posicao){novaLinha, novaColuna};
            }
        }
    }

    // Se não encontrou o caminho, retorna 0
    return 0;
}


int verCaminhoMatriz (Matriz *a) {
    int i, j;
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (a->matriz[i][j] == '1') {
                int i2, j2;
                for (i2 = i; i2 < a->linhas; i2++) {
                    if (i == i2) j2 = j + 1;
                    else j2 = 0;
                    for (; j2 < a->colunas; j2++) {
                        if (a->matriz[i2][j2] == '1' && !verCaminho (a, i, j, i2, j2)) {
                            return 0;
                        }
                    }
                }        
            }
        }
    }
    return 1;
}

//faz uma copia da matriz e transforma as letras maiusculas em 1 e o resto em 0
int verCaminhoMaiusculas (Matriz *a) {
    int r;
    Matriz copiaPara_1e0s = cria_Matriz_copia (a);
    r = verCaminhoMatriz (&copiaPara_1e0s);
    limpar_Matriz (&copiaPara_1e0s);
    return r;
}

void imprimirVerCaminhoMaiusculas(Matriz *a) {
    printf ("Não existe caminho entre: ");
    Matriz copiaPara_1e0s = cria_Matriz_copia (a);
    int i, j, r = 0;
    for (i = 0; i < copiaPara_1e0s.linhas; i++) {
        for (j = 0; j < copiaPara_1e0s.colunas; j++) {
            if (copiaPara_1e0s.matriz[i][j] == '1') {
                int i2, j2 = j+1;
                for (i2 = i; i2 < copiaPara_1e0s.linhas; i2++) {
                    for (; j2 < copiaPara_1e0s.linhas; j2++) {
                        if (copiaPara_1e0s.matriz[i2][j2] == '1') {
                            if (!verCaminho(&copiaPara_1e0s, i, j, i2, j2)) {
                                printf ("(%c%d, %c%d) ", j+97, i+1, j2+97, i2+1);
                                r++;
                                if (r==6) {
                                    printf("etc...\n");
                                    return; // Se já encontrou um par, não precisa continuar
                                }
                            }
                        }
                    }
                    j2 = 0;
                }
            }
        }
    }
    printf ("\n");
    limpar_Matriz (&copiaPara_1e0s);
}

// percorre todas as celulas da matriz e sempre que encontra uma letra maiuscula vai procurar se existe essa 
// letra minuscula na mesma linha/coluna
int verificar_Minusculas_Repetidas_com_Maiusculas (Matriz *a) {
    int i, j;
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (ehMaiuscula(a->matriz[i][j])) {
                int i2, j2;
                for (i2 = 0; i2 < a->linhas; i2++) {
                    if (a->matriz[i2][j] == a->matriz [i][j] + 32) return 0;
                }
                for (j2 = 0; j2 < a->colunas; j2++) {
                    if (a->matriz[i][j2] == a->matriz [i][j] + 32) return 0;
                }
            }
        }
    }
    return 1;
}

void risca_Minusculas_Repetidas (Matriz *a) {
    int i, j;
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (ehMaiuscula(a->matriz[i][j])) {
                int i2, j2;
                for (i2 = 0; i2 < a->linhas; i2++) {
                    if (a->matriz[i2][j] == a->matriz [i][j] + 32) a->matriz [i2][j] = '#';
                }
                for (j2 = 0; j2 < a->colunas; j2++) {
                    if (a->matriz[i][j2] == a->matriz [i][j] + 32) a->matriz [i][j2] = '#';
                }
            }
        }
    }
}

int ehMinuscula (char a) {
    if (a >= 97 && a <= 122) {
        return 1;
    }
    else return 0;
}


//para cada celula riscada, transforma as letras minusculas ortogonalmente adjacentes em maiusculas
void coloca_Em_Maiuscula_Pela_Riscada (Matriz *a) {
    int i, j;
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (a->matriz[i][j] == '#') {
                if (i > 0 && ehMinuscula(a->matriz[i-1][j])) a->matriz[i-1][j] = a->matriz[i-1][j] - 32;
                if (i < a->linhas - 1 && ehMinuscula(a->matriz[i+1][j])) a->matriz[i+1][j] = a->matriz[i+1][j] - 32;
                if (j > 0 && ehMinuscula(a->matriz[i][j-1])) a->matriz[i][j-1] = a->matriz[i][j-1] - 32;
                if (j < a->colunas - 1 && ehMinuscula(a->matriz[i][j+1])) a->matriz[i][j+1] = a->matriz[i][j+1] - 32;
            }
        }
    }
}

//para cada letra maiuscula, verifica se exatamente um vizinho ortogonal é minusculo e se isso for verdade, esse vizinho passa a maiusculo
void coloca_Em_Maiuscula_Pelo_Caminho (Matriz *a) {
    int i, j;

    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (ehMaiuscula(a->matriz[i][j])) {
                int cima     = (i > 0 && ehMinuscula(a->matriz[i - 1][j]));
                int baixo    = (i < a->linhas - 1 && ehMinuscula(a->matriz[i + 1][j]));
                int esquerda = (j > 0 && ehMinuscula(a->matriz[i][j - 1]));
                int direita  = (j < a->colunas - 1 && ehMinuscula(a->matriz[i][j + 1]));
                
                int Maiuscula = 
                    (i > 0 && ehMaiuscula(a->matriz[i - 1][j])) ||
                    (i < a->linhas - 1 && ehMaiuscula(a->matriz[i + 1][j])) ||
                    (j > 0 && ehMaiuscula(a->matriz[i][j - 1])) ||
                    (j < a->colunas - 1 && ehMaiuscula(a->matriz[i][j + 1]));
                    
                if (cima && !(baixo || esquerda || direita) && !Maiuscula) a->matriz[i-1][j] = a->matriz[i-1][j] - 32;
                if (baixo && !(cima || esquerda || direita) && !Maiuscula) a->matriz[i+1][j] = a->matriz[i+1][j] - 32;
                if (esquerda && !(cima || baixo || direita) && !Maiuscula) a->matriz[i][j-1] = a->matriz[i][j-1] - 32;
                if (direita && !(cima || baixo || esquerda) && !Maiuscula) a->matriz[i][j+1] = a->matriz[i][j+1] - 32; 
            }
        }
    }
}


// percorre a matriz e procura letras minusculas que estejam rodeadas ortogonalmente por letras maiusculas
// se a letra for minuscula e os vizinhos forem todos maiusculos entao essa letra sera "avaliada":
// se verCaminhoMaiuscula(letra) der verdadeiro, sera riscada, se nao vira maiuscula
void risca_Rodeada_Maiusculas (Matriz *a) {
    int i, j;

    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (ehMinuscula (a->matriz[i][j])) {    
                int Maiuscula = 1;

                // Verifica os vizinhos
                if (i > 0) Maiuscula &= ehMaiuscula(a->matriz[i - 1][j]); // Cima
                if (i < a->linhas - 1) Maiuscula &= ehMaiuscula(a->matriz[i + 1][j]); // Baixo
                if (j > 0) Maiuscula &= ehMaiuscula(a->matriz[i][j - 1]); // Esquerda
                if (j < a->colunas - 1) Maiuscula &= ehMaiuscula(a->matriz[i][j + 1]); // Direita
   
                if (Maiuscula) {
                    if (verCaminhoMaiusculas (a)) a->matriz[i][j] = '#';
                    else a->matriz[i][j] = a->matriz[i][j] - 32; 
                }
            }
        }
    }
}



int quant_Minusculas (Matriz *a) {
    int i, j, cont = 0;
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            if (ehMinuscula(a->matriz[i][j])) cont++;
        }
    }
    return cont;
}

// é util para para se por exemplo :
// Antes de o jogador fazer uma jogada, pode se criar uma copia da matriz atual.Se ele quiser desfazer a jogada, volta se a esssa copia
// VER MELHOR
Matriz cria_Matriz_igual (Matriz *a) {
    int i, j;
    Matriz copia = criar_Matriz(a->linhas, a->colunas);
    for (i = 0; i < a->linhas; i++) {
        for (j = 0; j < a->colunas; j++) {
            copia.matriz[i][j] = a->matriz[i][j];
        }
    }
    return copia;
}

int existe_Igual_na_Linha_ou_Coluna (Matriz *a, char letra, int linha, int coluna) {
    int i;
    // Verifica na linha
    for (i = 0; i < a->colunas; i++) {
        if (i != coluna && a->matriz[linha][i] == letra) return 1;
    }
    // Verifica na coluna
    for (i = 0; i < a->linhas; i++) {
        if (i != linha && a->matriz[i][coluna] == letra) return 1;
    }
    return 0;
}

#ifndef TESTING

int main (){
    char c, x;
    int y;
    Matriz mapa = {0, 0, NULL};
    Pilha jogadas;
    iniciarPilha (&jogadas);
    int ultima_linha = -1, ultima_coluna = -1;
    printf ("Carregue em c e dê ENTER para ver os comandos.\n");
    int contaD = 0; // contador para o comando 'd' (dicas)

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
        ultima_linha = -1; ultima_coluna = -1;  // reset
        printf ("Podes sempre utilizar o comando 'D' para obter dicas!\n");
    }
    else if (c == 'b') {
        if (scanf (" %c %d", &x, &y) != 2) printf ("Erro3");
        else if (x > (mapa.colunas - 1) + 'a' || y > mapa.linhas)
            printf ("A coordenada (%c, %d) não está dentro da matriz.\n", x, y);
        else if (!(mapa.matriz[y-1][x -'a'] >= 'a' && mapa.matriz[y-1][x -'a'] <= 'z'))
            printf ("A coordenada (%c, %d) não é uma letra minúscula\n", x, y);
        else {
            maiuscula_Elem (mapa, x, y);
            ultima_linha = y - 1;                // ← NOVO
            ultima_coluna = x - 'a';            // ← NOVO
            colocarMatrizNaPilha (&jogadas, mapa);
        }
    }
    else if (c == 'r') {
        if (scanf (" %c %d", &x, &y) != 2) printf ("Coordenadas inválidas\n");
        else if (x > (mapa.colunas - 1) + 'a' || y > mapa.linhas)
            printf ("A coordenada (%c, %d) não está dentro da matriz.\n", x, y);
        else if (mapa.matriz[y-1][x -'a'] == '#')
            printf ("A coordenada (%c, %d) já está riscada\n", x, y);
        else if (ehMaiuscula(mapa.matriz[y-1][x -'a']))
            printf ("Não é possível riscar a coordenada (%c, %d), pois é uma letra Maiúscula\n", x, y);
        else {
            riscar_Elem (mapa, x, y);
            ultima_linha = y - 1;                // ← NOVO
            ultima_coluna = x - 'a';            // ← NOVO
            colocarMatrizNaPilha (&jogadas, mapa);
        }
    }
    else if (c == 's') break;

    else if (c == 'd') {
        if (jogadas.topo->proximo == NULL)
            printf ("Não é possível recuar mais jogadas.\n");
        else {
            retirarMatrizDaPilha (&jogadas);
            restoraMatrizParaAUltimaJogada (&jogadas, &mapa);
            ultima_linha = -1; ultima_coluna = -1;  // reset
        }
    }
    else if (c == 'g') {
        char nome_Ficheiro[100];
        if (scanf ("%s", nome_Ficheiro) != 1) printf ("Erro2");
        gravar_ficheiro (mapa, nome_Ficheiro);
    }
    else if (c == 'v') {
        if (verificarLetrasRiscadas (&mapa) &&
            verificarLetrasRiscadasComMaiusculas (&mapa) &&
            verificarLetrasMaiusculasRepetidasLinha (&mapa) &&
            verificarLetrasMaiusculasRepetidasColuna (&mapa) &&
            verCaminhoMaiusculas (&mapa)) {
            printf ("Nenhuma regra violada.\n");
        }
        else {
            printf ("Coordenadas com Regras violadas:\n");
            if (!verificarLetrasRiscadas (&mapa)) imprimirLetrasRiscadas (&mapa);
            if (!verificarLetrasRiscadasComMaiusculas (&mapa)) imprimirLetrasRiscadasComMaiusculas (&mapa);
            if (!verificarLetrasMaiusculasRepetidasLinha (&mapa)) imprimirLetrasMaiusculasRepetidasLinha (&mapa);
            if (!verificarLetrasMaiusculasRepetidasColuna (&mapa)) imprimirLetrasMaiusculasRepetidasColuna (&mapa);
            if (!verCaminhoMaiusculas (&mapa)) imprimirVerCaminhoMaiusculas(&mapa); 
        }
    }
    else if (c == 'c') {
        printf ("Comandos disponíveis:\n");
        printf ("l (ficheiro) → Carregar jogo\n");
        printf ("g (ficheiro) → Gravar jogo\n");
        printf ("b x y → Colocar em Maiúscula\n");
        printf ("r x y → Riscar letra\n");
        printf ("d → Desfazer jogada\n");
        printf ("D → Receber uma dica\n");
        printf ("a → Atualizar matriz\n");
        printf ("A → Atualizar matriz repetidamente\n");
        printf ("v → Verificar regras\n");
        printf ("R → Resolver a matriz\n");
        printf ("s → Sair\n");
    }
    else if (c == 'a') {
        int quantidade_Elem_Matriz = mapa.linhas * mapa.colunas;
        coloca_Em_Maiuscula_Pela_Riscada (&mapa);
        risca_Minusculas_Repetidas (&mapa);
        coloca_Em_Maiuscula_Pelo_Caminho (&mapa);
        if (quant_Minusculas (&mapa) * 100 / quantidade_Elem_Matriz < 10) {
            risca_Rodeada_Maiusculas (&mapa);
            }
        colocarMatrizNaPilha (&jogadas, mapa);
        ultima_linha = -1; ultima_coluna = -1;
        printf("%d\n", quant_Minusculas (&mapa));
    }
    else if (c == 'A') {
        int matrizMudou = 1;
        int quantidade_Elem_Matriz = mapa.linhas * mapa.colunas; 
            while (matrizMudou) {
                matrizMudou = 0;

                Matriz copia = cria_Matriz_igual (&mapa);

                coloca_Em_Maiuscula_Pela_Riscada (&mapa);
                risca_Minusculas_Repetidas (&mapa);
                coloca_Em_Maiuscula_Pelo_Caminho (&mapa);
                if (quant_Minusculas (&mapa) * 100 / quantidade_Elem_Matriz < 10) {
                    risca_Rodeada_Maiusculas (&mapa);
                    }

                // Compare a matriz atual com a cópia
                for (int i = 0; i < mapa.linhas; i++) {
                    for (int j = 0; j < mapa.colunas; j++) {
                        if (copia.matriz[i][j] != mapa.matriz[i][j]) {
                            matrizMudou = 1;
                            break;
                        }
                    }
                    if (matrizMudou) break;
                }

                if (matrizMudou) {
                    imprimir_Matriz_Ponteiro (&mapa, ultima_linha, ultima_coluna);
                    printf ("\n");
                }
                

                limpar_Matriz(&copia);

            }
            colocarMatrizNaPilha (&jogadas, mapa);
            printf ("\n");

        }

    else if (c == 'R') {
        int comecaCiclo = 1, i = 0, j = 0;
        while (((!(verificarLetrasRiscadas (&mapa) &&
                 verificarLetrasRiscadasComMaiusculas (&mapa) &&
                 verificarLetrasMaiusculasRepetidasLinha (&mapa) &&
                 verificarLetrasMaiusculasRepetidasColuna (&mapa) &&
                 verCaminhoMaiusculas (&mapa)) || comecaCiclo) || quant_Minusculas (&mapa) > 0) && 
                 i < mapa.linhas && j < mapa.colunas) {
            comecaCiclo = 0;
            for (i = 0; i < mapa.linhas; i++) {
                for (j = 0; j < mapa.colunas; j++) {
                    if (ehMinuscula (mapa.matriz[i][j]) &&  existe_Igual_na_Linha_ou_Coluna (&mapa, mapa.matriz[i][j], i, j)) {
                        maiuscula_Elem (mapa, j + 'a', i + 1);
                        // Inicia o comando A
                        int matrizMudou = 1;
                        int quantidade_Elem_Matriz = mapa.linhas * mapa.colunas; 
                            while (matrizMudou) {
                                matrizMudou = 0;
                
                                Matriz copia = cria_Matriz_igual (&mapa);
                
                                coloca_Em_Maiuscula_Pela_Riscada (&mapa);
                                risca_Minusculas_Repetidas (&mapa);
                                coloca_Em_Maiuscula_Pelo_Caminho (&mapa);
                                if (quant_Minusculas (&mapa) * 100 / quantidade_Elem_Matriz < 10) {
                                    risca_Rodeada_Maiusculas (&mapa);
                                    }
                
                                // Compare a matriz atual com a cópia
                                for (int i = 0; i < mapa.linhas; i++) {
                                    for (int j = 0; j < mapa.colunas; j++) {
                                        if (copia.matriz[i][j] != mapa.matriz[i][j]) {
                                            matrizMudou = 1;
                                            break;
                                        }
                                    }
                                    if (matrizMudou) break;
                                }

                                // Se a matriz mudou, imprime a matriz atualizada
                                if (matrizMudou) {
                                    imprimir_Matriz_Ponteiro (&mapa, ultima_linha, ultima_coluna);
                                    printf ("\n");
                                }
                
                                limpar_Matriz(&copia);
                
                            }
                            // Fim do comando A sem colocar a Matriz na pilha.

                            if (verificarLetrasRiscadas (&mapa) &&
                            verificarLetrasRiscadasComMaiusculas (&mapa) &&
                            verificarLetrasMaiusculasRepetidasLinha (&mapa) &&
                            verificarLetrasMaiusculasRepetidasColuna (&mapa)) { // Se fizessemos v e não der erro (ignorando o caminho) colocamos a matriz na pila e avançamos para a proxima letra
                                colocarMatrizNaPilha (&jogadas, mapa);
                                ultima_linha = -1; ultima_coluna = -1;
                                imprimir_Matriz_Ponteiro (&mapa, ultima_linha, ultima_coluna);
                                printf ("\n");
                                if (quant_Minusculas (&mapa) > 0) printf ("Não houve erro na verificação por isso avança por esta jogada. \n\n");
                            } else {
                                restoraMatrizParaAUltimaJogada (&jogadas, &mapa);
                                printf ("Houve um erro por isso regressou nas jogadas.\n\n");
                            }
                    }
                }
            }
        }
    }
    else if (c == 'D') {
        // Dicas
        if (mapa.matriz == NULL) {
            printf ("Jogo não iniciado!\nCarregue em 'c' e dê ENTER para ver os comandos\n");
        }
        else if (((verificarLetrasRiscadas (&mapa) == 0) + 
                 (verificarLetrasMaiusculasRepetidasLinha (&mapa) == 0) +
                 (verificarLetrasMaiusculasRepetidasColuna (&mapa) == 0)) > 1) {
                printf ("Parece que tens várias regras violadas.\n");
                printf ("Podes sempre usar o comando 'd' para voltar atrás.\n");
        }
        else if (verificarLetrasRiscadas (&mapa) == 0) {
            printf ("Talvez seja melhor conferires se não há duas riscadas juntas.\n");
            printf ("Podes sempre usar o comando 'd' para voltar atrás.\n");
        }
        else if (verificarLetrasMaiusculasRepetidasLinha (&mapa) == 0) {
            printf ("Talvez seja melhor conferires se não há letras maiúsculas repetidas na linha.\n");
            printf ("Podes sempre usar o comando 'd' para voltar atrás.\n");
        }
        else if (verificarLetrasMaiusculasRepetidasColuna (&mapa) == 0) {
            printf ("Talvez seja melhor conferires se não há letras maiúsculas repetidas na coluna.\n");
            printf ("Podes sempre usar o comando 'd' para voltar atrás.\n");
        }
        else if (verificarLetrasRiscadasComMaiusculas (&mapa) == 0) {
            printf ("Talvez seja uma boa altura para usares os comandos 'a' ou 'A'.\n");
        }
        else if (quant_Minusculas (&mapa) == 0 && verCaminhoMaiusculas (&mapa) == 0) {
            printf ("Parece que não existe caminho entre as letras maiúsculas.\n");
            printf ("Talvez tenhas que usar o comando 'd' para voltar atrás várias vezes.\n");
        }
        else if (contaD < 4) {
            if (contaD == 0)printf ("Lembra-te que se duas ou mais letras minusculas iguais estiverem na mesma linha ou coluna, pelo menos uma delas tem que ser riscada.\n");
            else if (contaD == 1)printf ("Lembra-te que se uma letra maiúscula estiver na mesma linha ou coluna de uma letra minúscula igual, essa letra minúscula tem que ser riscada.\n");
            else if (contaD == 2)printf ("Procura letras minusculas iguais na mesma linha ou coluna, provavelmente vais ter que colocar alguma em Maiuscula. \n");
            else if (contaD == 3)printf ("Lembra-te de usares sempre os comandos disponiveis, caso não te lembres podes sempre usar o 'c' para veres uma lista.\n");
            contaD++;
        }
        else printf ("Parece estar tudo bem, continua. Mas lembra-te que as letras maiúsculas têm que ter um caminho entre si!\n");
    }

    else printf ("Comando Inválido\n");

    // Imprimir com realce na última jogada
    if (c == 'b' || c == 'r')
    imprimir_Matriz_Ponteiro (&mapa, ultima_linha, ultima_coluna);
    else
    imprimir_Matriz_Ponteiro (&mapa, -1, -1); // não realça nada
    
    if (mapa.matriz != NULL) printf ("Minusculas: %d\n", quant_Minusculas (&mapa));
    
    if (quant_Minusculas (&mapa) == 0) {
        if (verificarLetrasRiscadas (&mapa) &&
            verificarLetrasRiscadasComMaiusculas (&mapa) &&
            verificarLetrasMaiusculasRepetidasLinha (&mapa) &&
            verificarLetrasMaiusculasRepetidasColuna (&mapa) &&
            verCaminhoMaiusculas (&mapa) && mapa.matriz != NULL) {
                printf ("Jogo Ganho!\n");
                break;
        }
        else if (mapa.matriz == NULL && c != 'D') printf ("Jogo não iniciado!\nCarregue em 'c' e dê ENTER para ver os comandos\n");
        else if (c != 'D')printf ("Algo não está certo!\n");
    }

    
}

limpar_Pilha (&jogadas);
limpar_Matriz (&mapa);
return 0;
}
#endif