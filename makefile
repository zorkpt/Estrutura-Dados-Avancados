#vars
INCLUDES = Headers/clientes.h Headers/menugestor.h Headers/menuutilizador.h Headers/transportes.h Headers/gestores.h Headers/transacoes.h Headers/grafo.h
SOURCES = Model/clientes.c Model/dados.c View/login.c View/menu.c View/menugestor.c View/menuutilizador.c Model/transportes.c Controller/main.c Model/gestores.c Model/transacoes.c Controller/importexport.c Controller/verificacoes.c Model/grafo.c
OBJFILES = clientes.o dados.o login.o menu.o menugestor.o menuutilizador.o transportes.o main.o gestores.o transacoes.o importexport.o verificacoes.o grafo.o
EXEC = main

# Test-related variables
OBJFILES_TEST = tests/test_clients.o Model/clientes.o unity/src/unity.o Controller/verificacoes.o

# regras de sufixo
.SUFFIXES : .c .o .s

# como transformar um .c num .o ; $< --nome do ficheiro
.c.o:
	gcc -g -c $< -o $@

# como transformar um .s num .o ; $< --nome do ficheiro
.s.o:
	gcc -g -c $< -o $@

${EXEC} : ${OBJFILES}
	gcc -g -o ${EXEC} ${OBJFILES}

${OBJFILES} : ${SOURCES} ${INCLUDES}
	gcc -g -c ${SOURCES}

run: ${EXEC}
	./${EXEC}

clean:
	rm -f ${OBJFILES} ${EXEC} tests/test_clients.o Controller/verificacoes.o test_clients

debug:
	gdb -tui ${EXEC}

# Test-related rules

tests: test_clients
	./test_clients

tests/test_clients.o: tests/test_clients.c
	gcc -g -Iunity/src -c tests/test_clients.c -o tests/test_clients.o

Controller/verificacoes.o: Controller/verificacoes.c
	gcc -g -c Controller/verificacoes.c -o Controller/verificacoes.o

test_clients: ${OBJFILES_TEST}
	gcc -g -Iunity/src -o test_clients ${OBJFILES_TEST}
