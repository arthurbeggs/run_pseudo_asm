.RECIPEPREFIX = >

# Variáveis
montador_sources   = src/montador/montador.c src/montador/error_messages.h \
					 src/montador/functions.h src/montador/montagem.h \
					 src/montador/pre_processamento.h \
					 src/montador/processa_macros.h

ligador_sources    = src/ligador/ligador.c src/ligador/functions.h

carregador_sources = src/carregador/carregador.c src/carregador/functions.h

# Define compilador utilizado
CC = gcc

# Define flags do compilador
CC_FLAGS = -Wall -g


# Compila montador, ligador e carregador
all : montador ligador carregador


# Compila o montador
montador : montador.o
>	$(CC) $(CC_FLAGS) -o montador montador.o


montador.o : $(montador_sources)
>	$(CC) $(CC_FLAGS) -c src/montador/montador.c


# Compila o ligador
ligador : ligador.o
>	$(CC) $(CC_FLAGS) -o ligador ligador.o


ligador.o : $(ligador_sources)
>	$(CC) $(CC_FLAGS) -c src/ligador/ligador.c


# Compila o carregador
carregador : carregador.o
>	$(CC) $(CC_FLAGS) -o carregador carregador.o


carregador.o : $(carregador_sources)
>	$(CC) $(CC_FLAGS) -c src/carregador/carregador.c



# Apaga executáveis e arquivos objetos
.PHONY: clean
clean :
>	- rm montador montador.o ligador ligador.o carregador carregador.o
