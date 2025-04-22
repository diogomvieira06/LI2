#include<stdio.h>
#include<string.h>
#include<CUnit/Basic.h>
#include<stdlib.h>
#include"jogo.h"


void test_criar_limpar_matriz(void) {
    Matriz m = criar_Matriz(3, 3);

    CU_ASSERT(m.linhas == 3);
    CU_ASSERT(m.colunas == 3);
    CU_ASSERT_PTR_NOT_NULL(m.matriz);

    for (int i = 0; i < 3; i++) {
        CU_ASSERT_PTR_NOT_NULL(m.matriz[i]);
    }
    
    limpar_Matriz(&m);
    CU_ASSERT_PTR_NULL(m.matriz);
    CU_ASSERT(m.linhas == 0);
    CU_ASSERT(m.colunas == 0);
}

//3 testes para a funçao que torna os elementos em maiusculo
void test_maiuscula_Elem(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = 'a';
    maiuscula_Elem(m, 'a', 1);
    CU_ASSERT(m.matriz[0][0] == 'A');
    limpar_Matriz(&m);
}

void test_maiuscula_Elem_ja_maiuscula(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = 'B';  // já está em maiúscula
    maiuscula_Elem(m, 'a', 1);  // coordenada (a,1) = [0][0]
    CU_ASSERT(m.matriz[0][0] == 'B');  // Deve continuar 'B'
    limpar_Matriz(&m);
}

void test_maiuscula_Elem_coordenada_invalida(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = 'a';
    maiuscula_Elem(m, 'd', 5);  // coordenada (d,5) está fora dos limites
    CU_ASSERT(m.matriz[0][0] == 'a');  // Nada deve ter mudado
    limpar_Matriz(&m);
}



//3 testes para a funçao que risca coordenadas
void test_riscar_Elem(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[1][1] = 'b';
    riscar_Elem(m, 'b', 2);
    CU_ASSERT(m.matriz[1][1] == '#');
    limpar_Matriz(&m);
}

void test_riscar_Elem_elemento_ja_riscado(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = '#';  
    riscar_Elem(m, 'a', 1);  
    CU_ASSERT(m.matriz[0][0] == '#');  
    limpar_Matriz(&m);
}

void test_riscar_Elem_coordenada_invalida(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = 'a';
    riscar_Elem(m, 'd', 5); 
    CU_ASSERT(m.matriz[0][0] == 'a'); 
    limpar_Matriz(&m);
}

void test_ler_ficheiro(void) {
    FILE *f = fopen("tabuleiro_teste.txt", "w");
    fprintf(f, "2 2\nab\ncd\n");
    fclose(f);

    Matriz m = ler_ficheiro("tabuleiro_teste.txt");
    CU_ASSERT(m.linhas == 2);
    CU_ASSERT(m.colunas == 2);
    CU_ASSERT(m.matriz[0][0] == 'a');
    CU_ASSERT(m.matriz[0][1] == 'b');
    CU_ASSERT(m.matriz[1][0] == 'c');
    CU_ASSERT(m.matriz[1][1] == 'd');

    limpar_Matriz(&m);
    remove("tabuleiro_teste.txt");
}

void test_ler_ficheiro2(void) {

    Matriz m = ler_ficheiro("j1.txt");
    CU_ASSERT(m.linhas == 5);
    CU_ASSERT(m.colunas == 5);
    CU_ASSERT(m.matriz[0][0] == 'e');
    CU_ASSERT(m.matriz[0][3] == 'd');
    CU_ASSERT(m.matriz[2][0] == 'b');
    CU_ASSERT(m.matriz[4][4] == 'b');

    limpar_Matriz(&m);
}

///////////////////////////////////////////
//TESTES DA TAREFA 2
///////////////////////////////////////////

void test_ehMaiuscula(void) {
    CU_ASSERT(ehMaiuscula('A') == 1);
    CU_ASSERT(ehMaiuscula('a') == 0);
    CU_ASSERT(ehMaiuscula(' ') == 0);
    CU_ASSERT(ehMaiuscula('#') == 0);
}


//6 testes para a funçao que verifica as letras riscadas(e as suas otogonais)
void test_verificarLetrasRiscadas_vazia(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = 'a';
    m.matriz[0][1] = 'b';
    m.matriz[1][0] = 'c';
    m.matriz[1][1] = 'd';

    CU_ASSERT(verificarLetrasRiscadas(&m) == 1);  // nenhum '#', válido
    limpar_Matriz(&m);
}

void test_verificarLetrasRiscadas_separados(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = '#';
    m.matriz[0][1] = 'a';
    m.matriz[1][0] = 'b';
    m.matriz[1][1] = '#';

    CU_ASSERT(verificarLetrasRiscadas(&m) == 1);  // separados → válido
    limpar_Matriz(&m);
}

void test_verificarLetrasRiscadas_juntos_horizontal(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = '#';
    m.matriz[0][1] = '#';
    m.matriz[1][0] = 'a';
    m.matriz[1][1] = 'b';

    CU_ASSERT(verificarLetrasRiscadas(&m) == 0);  // violação
    limpar_Matriz(&m);
}

void test_verificarLetrasRiscadas_juntos_vertical(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = '#';
    m.matriz[1][0] = '#';
    m.matriz[0][1] = 'a';
    m.matriz[1][1] = 'b';

    CU_ASSERT(verificarLetrasRiscadas(&m) == 0);  // violação
    limpar_Matriz(&m);
}

void test_verificarLetrasRiscadas_tudo_riscado(void) {
    Matriz m = criar_Matriz(2, 2);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            m.matriz[i][j] = '#';

    CU_ASSERT(verificarLetrasRiscadas(&m) == 0);  // tudo junto → inválido
    limpar_Matriz(&m);
}

void test_verificarLetrasRiscadas_diagonal(void) {
    Matriz m = criar_Matriz(3, 3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m.matriz[i][j] = 'a';

    m.matriz[0][0] = '#';
    m.matriz[1][1] = '#';
    m.matriz[2][2] = '#';

    CU_ASSERT(verificarLetrasRiscadas(&m) == 1);  // diagonal não conta → válido
    limpar_Matriz(&m);
}

//3 testes para a funçao verificarLetrasRiscadasComMaiusculas sendo estes os testes mais uteis
void test_riscada_com_minuscula_ao_lado(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = '#';
    m.matriz[0][1] = 'b';  // minúscula
    m.matriz[1][0] = 'A';
    m.matriz[1][1] = 'B';

    CU_ASSERT(verificarLetrasRiscadasComMaiusculas(&m) == 0);
    limpar_Matriz(&m);
}

void test_dois_riscados_juntos(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = '#';
    m.matriz[0][1] = '#';  // o segundo '#' não é maiúscula
    m.matriz[1][0] = 'A';
    m.matriz[1][1] = 'B';

    CU_ASSERT(verificarLetrasRiscadasComMaiusculas(&m) == 0);
    limpar_Matriz(&m);
}

void test_varios_riscados_com_maiusculas_ao_redor(void) {
    Matriz m = criar_Matriz(3, 3);
    m.matriz[0][0] = 'A'; m.matriz[0][1] = 'B'; m.matriz[0][2] = 'C';
    m.matriz[1][0] = '#'; m.matriz[1][1] = 'D'; m.matriz[1][2] = '#';
    m.matriz[2][0] = 'F'; m.matriz[2][1] = 'G'; m.matriz[2][2] = 'H';

    CU_ASSERT(verificarLetrasRiscadasComMaiusculas(&m) == 1);
    limpar_Matriz(&m);
}


// 6 testes para a funçao verificarLetrasMaiusculasRepetidasLinha
void test_sem_maiusculas(void) {
    Matriz m = criar_Matriz(2, 3);
    m.matriz[0][0] = 'a'; m.matriz[0][1] = 'b'; m.matriz[0][2] = 'c';
    m.matriz[1][0] = 'd'; m.matriz[1][1] = 'e'; m.matriz[1][2] = 'f';

    CU_ASSERT(verificarLetrasMaiusculasRepetidasLinha(&m) == 1);
    limpar_Matriz(&m);
}

void test_maiusculas_sem_repeticao(void) {
    Matriz m = criar_Matriz(2, 3);
    m.matriz[0][0] = 'A'; m.matriz[0][1] = 'B'; m.matriz[0][2] = 'C';
    m.matriz[1][0] = 'D'; m.matriz[1][1] = 'E'; m.matriz[1][2] = 'F';

    CU_ASSERT(verificarLetrasMaiusculasRepetidasLinha(&m) == 1);
    limpar_Matriz(&m);
}

void test_maiusculas_repetidas_na_linha(void) {
    Matriz m = criar_Matriz(2, 3);
    m.matriz[0][0] = 'A'; m.matriz[0][1] = 'B'; m.matriz[0][2] = 'A';  // 'A' repetido
    m.matriz[1][0] = 'C'; m.matriz[1][1] = 'D'; m.matriz[1][2] = 'E';

    CU_ASSERT(verificarLetrasMaiusculasRepetidasLinha(&m) == 0);
    limpar_Matriz(&m);
}

void test_minusculas_repetidas(void) {
    Matriz m = criar_Matriz(2, 3);
    m.matriz[0][0] = 'a'; m.matriz[0][1] = 'b'; m.matriz[0][2] = 'a';  // minúscula repetida
    m.matriz[1][0] = 'c'; m.matriz[1][1] = 'd'; m.matriz[1][2] = 'e';

    CU_ASSERT(verificarLetrasMaiusculasRepetidasLinha(&m) == 1);
    limpar_Matriz(&m);
}

void test_matriz_vazia(void) {
    Matriz m = criar_Matriz(2, 3);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            m.matriz[i][j] = ' ';

    CU_ASSERT(verificarLetrasMaiusculasRepetidasLinha(&m) == 1);
    limpar_Matriz(&m);
}
void test_mesma_maiuscula_em_linhas_diferentes(void) {
    Matriz m = criar_Matriz(2, 3);
    m.matriz[0][0] = 'A'; m.matriz[0][1] = 'B'; m.matriz[0][2] = 'C';
    m.matriz[1][0] = 'A'; m.matriz[1][1] = 'D'; m.matriz[1][2] = 'E';

    CU_ASSERT(verificarLetrasMaiusculasRepetidasLinha(&m) == 1);
    limpar_Matriz(&m);
}

// 6 testes para a funçao verificarLetrasMaiusculasRepetidasColuna
void test_coluna_sem_maiusculas(void) {
    Matriz m = criar_Matriz(2, 3);
    m.matriz[0][0] = 'a'; m.matriz[0][1] = 'b'; m.matriz[0][2] = 'c';
    m.matriz[1][0] = 'd'; m.matriz[1][1] = 'e'; m.matriz[1][2] = 'f';

    CU_ASSERT(verificarLetrasMaiusculasRepetidasColuna(&m) == 1);
    limpar_Matriz(&m);
}

void test_colunas_sem_repeticao(void) {
    Matriz m = criar_Matriz(2, 3);
    m.matriz[0][0] = 'A'; m.matriz[0][1] = 'B'; m.matriz[0][2] = 'C';
    m.matriz[1][0] = 'D'; m.matriz[1][1] = 'E'; m.matriz[1][2] = 'F';

    CU_ASSERT(verificarLetrasMaiusculasRepetidasColuna(&m) == 1);
    limpar_Matriz(&m);
}

void test_coluna_com_repeticao_maiusculas(void) {
    Matriz m = criar_Matriz(2, 3);
    m.matriz[0][0] = 'A'; m.matriz[0][1] = 'B'; m.matriz[0][2] = 'C';
    m.matriz[1][0] = 'A'; m.matriz[1][1] = 'D'; m.matriz[1][2] = 'E';  // 'A' repetida na coluna 0

    CU_ASSERT(verificarLetrasMaiusculasRepetidasColuna(&m) == 0);
    limpar_Matriz(&m);
}

void test_colunas_com_minusculas_repetidas(void) {
    Matriz m = criar_Matriz(2, 3);
    m.matriz[0][0] = 'a'; m.matriz[0][1] = 'b'; m.matriz[0][2] = 'c';
    m.matriz[1][0] = 'a'; m.matriz[1][1] = 'd'; m.matriz[1][2] = 'e';

    CU_ASSERT(verificarLetrasMaiusculasRepetidasColuna(&m) == 1); // minúsculas podem repetir
    limpar_Matriz(&m);
}

void test_colunas_matriz_vazia(void) {
    Matriz m = criar_Matriz(2, 3);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            m.matriz[i][j] = ' ';

    CU_ASSERT(verificarLetrasMaiusculasRepetidasColuna(&m) == 1);
    limpar_Matriz(&m);
}

void test_mesma_maiuscula_em_colunas_diferentes(void) {
    Matriz m = criar_Matriz(2, 3);
    m.matriz[0][0] = 'A'; m.matriz[0][1] = 'B'; m.matriz[0][2] = 'C';
    m.matriz[1][0] = 'D'; m.matriz[1][1] = 'A'; m.matriz[1][2] = 'E';  // 'A' aparece em colunas diferentes

    CU_ASSERT(verificarLetrasMaiusculasRepetidasColuna(&m) == 1);
    limpar_Matriz(&m);
}

//2 testes para a parte de iniciar pilha
void test_iniciarPilha_deveInicializarComTopoNull() {
    Pilha p;
    iniciarPilha(&p);
    CU_ASSERT_PTR_NULL(p.topo);
}

void test_iniciarPilha_2() { // neste teste a pilha ja tem valores na memoria mas qnd o jogo começa ele apaga esses valores e ent a pilha fica vazia
    Pilha p;
    Node nodoExemplo;
    p.topo = &nodoExemplo;
    iniciarPilha(&p);
    CU_ASSERT_PTR_NULL(p.topo);
}


// para a funçao colocarMatrizNaPilha que coloca uma matriz na pilha
void test_colocarMatrizNaPilha_umaMatriz() {
    Pilha p;
    iniciarPilha(&p);

    Matriz m;
    m.linhas = 2;
    m.colunas = 2;
    m.matriz = malloc(2 * sizeof(char*));
    for (int i = 0; i < 2; i++) {
        m.matriz[i] = malloc(2 * sizeof(char));
        for (int j = 0; j < 2; j++) {
            m.matriz[i][j] = 'A' + i + j;
        }
    }

    colocarMatrizNaPilha(&p, m);

    CU_ASSERT_PTR_NOT_NULL(p.topo);
    CU_ASSERT_EQUAL(p.topo->estado.linhas, 2);
    CU_ASSERT_EQUAL(p.topo->estado.colunas, 2);
    CU_ASSERT_EQUAL(p.topo->estado.matriz[0][0], 'A');
    CU_ASSERT_EQUAL(p.topo->estado.matriz[1][1], 'C');

    // Libertar matriz original
    for (int i = 0; i < m.linhas; i++) {
        free(m.matriz[i]);
    }
    free(m.matriz);

    // Libertar a matriz copiada dentro da pilha
    for (int i = 0; i < p.topo->estado.linhas; i++) {
        free(p.topo->estado.matriz[i]);
    }
    free(p.topo->estado.matriz);

    free(p.topo);
}

//2 testes para a funçao retirarMatrizDaPilha que retira uma matriz do topo da pilha e apaga essa mesma memoria
void test_retirarMatrizDaPilha_umElemento() {
    Pilha p;
    iniciarPilha(&p);

    Matriz m;
    m.linhas = 2;
    m.colunas = 2;
    m.matriz = malloc(2 * sizeof(char*));
    for (int i = 0; i < 2; i++) {
        m.matriz[i] = malloc(2 * sizeof(char));
        for (int j = 0; j < 2; j++) {
            m.matriz[i][j] = 'X';
        }
    }

    colocarMatrizNaPilha(&p, m);

    // Libertar a matriz original (a cópia foi feita dentro da pilha)
    for (int i = 0; i < m.linhas; i++) free(m.matriz[i]);
    free(m.matriz);

    retirarMatrizDaPilha(&p);

    CU_ASSERT_PTR_NULL(p.topo); 
}

void test_retirarMatrizDaPilha_pilhaVazia() {
    Pilha p;
    iniciarPilha(&p); // topo = NULL

    retirarMatrizDaPilha(&p); // Deve apenas mostrar a mensagem, sem crash

    CU_ASSERT_PTR_NULL(p.topo); // Continua NULL, sem alteração
}

void test_restoraMatrizParaAUltimaJogada_copiaCorreta() {
    Pilha p;
    iniciarPilha(&p);

    // Criar matriz original (2x2)
    Matriz m;
    m.linhas = 2;
    m.colunas = 2;
    m.matriz = malloc(2 * sizeof(char*));
    for (int i = 0; i < 2; i++) {
        m.matriz[i] = malloc(2 * sizeof(char));
        for (int j = 0; j < 2; j++) {
            m.matriz[i][j] = 'A' + i * 2 + j;  // 'A', 'B', 'C', 'D'
        }
    }

    // Inserir na pilha
    colocarMatrizNaPilha(&p, m);

    // Criar matriz "atual" (com espaço alocado)
    Matriz atual;
    atual.linhas = 2;
    atual.colunas = 2;
    atual.matriz = malloc(2 * sizeof(char*));
    for (int i = 0; i < 2; i++) {
        atual.matriz[i] = malloc(2 * sizeof(char));
    }

    // Chamar a função a testar
    restoraMatrizParaAUltimaJogada(&p, &atual);

    // Verificações
    CU_ASSERT_EQUAL(atual.matriz[0][0], 'A');
    CU_ASSERT_EQUAL(atual.matriz[0][1], 'B');
    CU_ASSERT_EQUAL(atual.matriz[1][0], 'C');
    CU_ASSERT_EQUAL(atual.matriz[1][1], 'D');

    // Libertar matriz original
    for (int i = 0; i < 2; i++) free(m.matriz[i]);
    free(m.matriz);

    // Libertar a matriz copiada na pilha
    for (int i = 0; i < 2; i++) free(p.topo->estado.matriz[i]);
    free(p.topo->estado.matriz);
    free(p.topo);

    // Libertar matriz atual
    for (int i = 0; i < 2; i++) free(atual.matriz[i]);
    free(atual.matriz);
}

void test_limparPilha_umNodo() {
    Pilha p;
    iniciarPilha(&p);

    // Criar matriz 2x2 simples
    Matriz m;
    m.linhas = 2;
    m.colunas = 2;
    m.matriz = malloc(2 * sizeof(char*));
    for (int i = 0; i < 2; i++) {
        m.matriz[i] = malloc(2 * sizeof(char));
        m.matriz[i][0] = 'A';
        m.matriz[i][1] = 'B';
    }

    colocarMatrizNaPilha(&p, m);

    // Libertar a matriz original (a cópia está na pilha)
    for (int i = 0; i < 2; i++) free(m.matriz[i]);
    free(m.matriz);

    limpar_Pilha(&p);

    CU_ASSERT_PTR_NULL(p.topo);  // Pilha deve estar vazia
}














int main() {
    CU_initialize_registry();

    CU_pSuite Tarefa1 = CU_add_suite("Testes da Tarefa1", 0, 0);
    CU_add_test(Tarefa1, "Testar criar e limpar matriz", test_criar_limpar_matriz);
    CU_add_test(Tarefa1, "Testar pintar maiúscula", test_maiuscula_Elem);
    CU_add_test(Tarefa1, "Testar riscar célula", test_riscar_Elem);
    CU_add_test(Tarefa1, "Testar ler ficheiro", test_ler_ficheiro);
    CU_add_test(Tarefa1, "Testar ler ficheiro2", test_ler_ficheiro2);
    CU_add_test(Tarefa1, "Riscar elemento já riscado", test_riscar_Elem_elemento_ja_riscado);
    CU_add_test(Tarefa1, "Riscar elemento fora da matriz", test_riscar_Elem_coordenada_invalida);

    //testes tarefa 2

    CU_pSuite Tarefa2 = CU_add_suite("Testes da Tarefa2", 0, 0);
    CU_add_test(Tarefa2, "Testar ehMaiuscula", test_ehMaiuscula);
    CU_add_test(Tarefa2, "Matriz vazia", test_verificarLetrasRiscadas_vazia);
    CU_add_test(Tarefa2, "Dois riscos separados", test_verificarLetrasRiscadas_separados);
    CU_add_test(Tarefa2, "Dois riscos juntos (horizontal)", test_verificarLetrasRiscadas_juntos_horizontal);
    CU_add_test(Tarefa2, "Dois riscos juntos (vertical)", test_verificarLetrasRiscadas_juntos_vertical);
    CU_add_test(Tarefa2, "Matriz completamente riscada", test_verificarLetrasRiscadas_tudo_riscado);
    CU_add_test(Tarefa2, "Riscos em diagonal", test_verificarLetrasRiscadas_diagonal);
    CU_add_test(Tarefa2, "Riscado com minúscula ao lado", test_riscada_com_minuscula_ao_lado);
    CU_add_test(Tarefa2, "Dois riscados juntos", test_dois_riscados_juntos);
    CU_add_test(Tarefa2, "Vários riscados com maiúsculas ao redor", test_varios_riscados_com_maiusculas_ao_redor);
    CU_add_test(Tarefa2, "Sem maiúsculas", test_sem_maiusculas);
    CU_add_test(Tarefa2, "Maiúsculas sem repetição", test_maiusculas_sem_repeticao);
    CU_add_test(Tarefa2, "Maiúsculas repetidas na mesma linha", test_maiusculas_repetidas_na_linha);
    CU_add_test(Tarefa2, "Minúsculas repetidas (válido)", test_minusculas_repetidas);
    CU_add_test(Tarefa2, "Matriz completamente vazia", test_matriz_vazia);
    CU_add_test(Tarefa2, "Mesma maiúscula em linhas diferentes", test_mesma_maiuscula_em_linhas_diferentes);
    CU_add_test(Tarefa2, "Coluna sem maiúsculas", test_coluna_sem_maiusculas);
    CU_add_test(Tarefa2, "Colunas sem repetição", test_colunas_sem_repeticao);
    CU_add_test(Tarefa2, "Coluna com repetição de maiúsculas", test_coluna_com_repeticao_maiusculas);
    CU_add_test(Tarefa2, "Colunas com minúsculas repetidas", test_colunas_com_minusculas_repetidas);
    CU_add_test(Tarefa2, "Colunas com matriz vazia", test_colunas_matriz_vazia);
    CU_add_test(Tarefa2, "Mesma maiúscula em colunas diferentes", test_mesma_maiuscula_em_colunas_diferentes);
    CU_add_test(Tarefa2, "iniciarPilha deve inicializar com topo NULL", test_iniciarPilha_deveInicializarComTopoNull);
    CU_add_test(Tarefa2, "iniciarPilha deve limpar valores antigos", test_iniciarPilha_2);
    CU_add_test(Tarefa2, "Inserir uma matriz simples na pilha", test_colocarMatrizNaPilha_umaMatriz);
    CU_add_test(Tarefa2, "Retirar matriz de uma pilha com um elemento", test_retirarMatrizDaPilha_umElemento);
    CU_add_test(Tarefa2, "Retirar matriz de uma pilha vazia", test_retirarMatrizDaPilha_pilhaVazia);
    CU_add_test(Tarefa2, "Restaurar matriz a partir do topo da pilha", test_restoraMatrizParaAUltimaJogada_copiaCorreta);
    CU_add_test(Tarefa2, "Limpar pilha com 1 nodo", test_limparPilha_umNodo);












    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}



