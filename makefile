#vars
INCLUDES = Headers/clientes.h Headers/menugestor.h Headers/menuutilizador.h Headers/transportes.h Headers/gestores.h Headers/transacoes.h
SOURCES = Model/clientes.c Model/dados.c View/login.c View/menu.c View/menugestor.c View/menuutilizador.c Model/transportes.c Controller/main.c Model/gestores.c Model/transacoes.c Controller/exportarparabin.c Controller/verificacoes.c
OBJFILES = clientes.o dados.o login.o menu.o menugestor.o menuutilizador.o transportes.o main.o gestores.o transacoes.o exportarparabin.o verificacoes.o
EXEC = main

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
	rm -f ${OBJFILES} ${EXEC}

debug:
	gdb -tui ${EXEC}
