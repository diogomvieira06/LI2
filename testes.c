#include<stdio.h>
#include<string.h>
#include<CUnit/Basic.h>
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

void test_maiuscula_Elem(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[0][0] = 'a';
    maiuscula_Elem(m, 'a', 1);
    CU_ASSERT(m.matriz[0][0] == 'A');
    limpar_Matriz(&m);
}

void test_riscar_Elem(void) {
    Matriz m = criar_Matriz(2, 2);
    m.matriz[1][1] = 'b';
    riscar_Elem(m, 'b', 2);
    CU_ASSERT(m.matriz[1][1] == '#');
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

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes do Projeto", 0, 0);
    CU_add_test(suite, "Testar criar e limpar matriz", test_criar_limpar_matriz);
    CU_add_test(suite, "Testar pintar maiúscula", test_maiuscula_Elem);
    CU_add_test(suite, "Testar riscar célula", test_riscar_Elem);
    CU_add_test(suite, "Testar ler ficheiro", test_ler_ficheiro);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}



