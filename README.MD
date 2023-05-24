# Projecto de Avaliação - Estruturas de Dados Avançadas 
## Hugo Poças 26339

Desenvolver uma solução de software para agilizar a gestão da mobilidade urbana (registro, uso) num contexto de smart city, usando estruturas de dados dinâmicas, armazenamento de ficheiros, modularização e documentação adequada.

## Status atual

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