# Projecto de Avaliação - Estruturas de Dados Avançadas 
## Hugo Poças 26339

Desenvolver uma solução de software para agilizar a gestão da mobilidade urbana (registro, uso) num contexto de smart city, usando estruturas de dados dinâmicas, armazenamento de ficheiros, modularização e documentação adequada.



## Compilação e Execução

Este projeto utiliza um Makefile para compilar e executar o código. 

Aqui estão as opções disponíveis:

```` make run ````
Esta opção compila todos os ficheiros .c no projecto e executa o programa.


```` make clean ````
Esta opção limpa todos os ficheiros objeto e binários gerados durante a compilação.






## Status Fase 1

Para a fase 1 foi implementado:

1. Gestão de data de Clientes, Gestores, Transportes e transações.
2. Exportar e ler dados para/de ficheiros binarios
3. Várias verificações e validações.
4. Sistema de login para utilizadores e gestores.
5. Menu de utilizador e gestor.

## Estrutura de Ficheiros

### Controller

- importexport.c: Lida com a exportação/importação de dados de ficheiros binários.
- main.c: Ficheiro principal do programa, onde a execução começa.
- verificacoes.c: Contém implementações de funções de verificação.


### Data

- Contém subdiretórios para Ficheiros binários (Bin) e CSV (Csv) usados no projeto.

### Model

- clientes.c: Implementa funções relacionadas aos clientes.
- dados.c: Funções para leitura e manipulação de dados do projeto.
- gestores.c: Implementa funções relacionadas aos gestores.
- transacoes.c: Implementa funções relacionadas às transações.
- transportes.c: Implementa funções relacionadas aos transportes.

### View

- login.c: Implementa funções de login e autenticação.
- menu.c: Contém funções para mostrar e interagir com o menu principal.
- menugestor.c: Implementa funções para mostrar e interagir com o menu do gestor.
- menuutilizador.c: Implementa funções para mostrar e interagir com o menu do utilizador.


### Headers
- verificacoes.h: Ficheiro header com declarações de funções de verificação.
- importexport.h: Ficheiro header que contêm declarações de funções para várias funções utilitárias.
- clientes.h: Ficheiro header com declarações de funções e estruturas relacionadas aos clientes.
- gestores.h: Ficheiro header com declarações de funções e estruturas relacionadas aos gestores.
- transacoes.h: Ficheiro header com declarações de funções e estruturas relacionadas às transações.
- transportes.h: Ficheiro header com declarações de funções e estruturas relacionadas aos transportes.
- menugestor.h: Ficheiro header com declarações de funções relacionadas ao menu do gestor.
- menuutilizador.h: Ficheiro header com declarações de funções relacionadas ao menu do utilizador.


## Status Final Fase 2

No decorrer da fase 2, foram implementadas as seguintes características:

1. Gestão de dados de vertices (cidades no grafo de transporte).
2. Gestão de dados de arestas (rotas entre as cidades no grafo de transporte).
3. Implementação e integração de algoritmos de busca para traçar rotas entre cidades.
4. Exportar e ler dados de vertices e arestas para/de ficheiros binários.
5. Ajustes e melhorias nas validações existentes.
6. Integração dos novos tipos de dados na interface de utilizador e gestor.

## Estrutura de Ficheiros

### Controller
- busca.c: Implementa funções de busca no grafo
- caminho.c: Implementa funções para traçar caminhos no grafo.
- fila.c: Implementa funções para manipular filas.
- importexport.c: Lida com a exportação/importação de dados de ficheiros binários.
- main.c: Ficheiro principal do programa, onde a execução começa.
- verificacoes.c: Contém implementações de funções de verificação.

### Model
- clientes.c
- gestores.c
- grafo.c:  # Implementa funções relacionadas ao grafo.
- transacoes.c
- transportes.c

### View

- login.c: Implementa funções de login e autenticação.
- menu.c: Contém funções para mostrar e interagir com o menu principal.
- menugestor.c: Implementa funções para mostrar e interagir com o menu do gestor.
- menuutilizador.c: Implementa funções para mostrar e interagir com o menu do utilizador.


### Data

- Contém subdiretórios para Ficheiros binários (Bin) e CSV (Csv) usados no projeto.





### Headers
- busca.h: Ficheiro header com declarações de funções de busca.
- caminho.h: Ficheiro header com declarações de funções de caminho.
- clientes.h
- fila.h : Ficheiro header com declarações de funções de fila.
- gestores.h
- grafo.h: Ficheiro header com declarações de funções e estruturas do grafo.
- importexport.h
- menugestor.h
- menuutilizador.h
- transacoes.h
- transportes.h
- verificacoes.h
- viagem.h: Ficheiro header com declarações de funções e estruturas relacionadas a viagens.

