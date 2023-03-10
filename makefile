#vars
INCLUDES = estruturas.h funcoes.h menugestor.h menuutilizador.h clientes.h transportes.h gestores.h transacoes.h
SOURCES = clientes.c dados.c login.c menu.c menugestor.c menuutilizador.c transportes.c main.c gestores.c transacoes.c exportarparabin.c
OBJFILES = clientes.o dados.o login.o menu.o menugestor.o menuutilizador.o transportes.o main.o gestores.o transacoes.o exportarparabin.o
EXEC = main

# regras de sufixo
.SUFIXES : .c .o .s

# como transformar um .c num .o ; $< --nome do ficheiro
.c.o:
	gcc -g -c $<

# como transformar um .s num .o ; $< --nome do ficheiro
.s.o:
	gcc -g -c $<

${EXEC} : ${OBJFILES}
	gcc -g -o ${EXEC} ${OBJFILES}

${OBJFILES} : ${SOURCES} ${INCLUDES}

run: ${EXEC}
	./${EXEC}

clean:
	rm -f ${OBJFILES} ${EXEC}

debug:
	gdb -tui ${EXEC}
	