CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -g -fprofile-arcs -ftest-coverage
LDLIBS = -lcunit

HDR = jogo.h

# Target para o executável principal do jogo
jogo: jogo.c $(HDR)
	$(CC) $(CFLAGS) -o jogo jogo.c 

# Target para os testes com CUnit
testar: testes.c jogo.c $(HDR)
	$(CC) $(CFLAGS) -DTESTING -o testar testes.c jogo.c $(LDLIBS)
	./testar

gcov: testar
	gcov testar-jogo.gcno
	gcov testar-testes.gcno

# Limpeza de ficheiros gerados
clean:
	rm -f jogo testar *.gcda *.gcno *.gcov