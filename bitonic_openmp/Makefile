FLAGS=-O3 -fopenmp # adicionado -fopenmp pra rodar openmp

CC=gcc # adicionei gcc pra rodar no nosso pczinho
#CC=icc # intel noggers descomentar para rodar la no pczao

RM=rm -f

EXEC=bitonic

all: $(EXEC)

$(EXEC): $(EXEC).c
	$(CC) $(FLAGS) $(EXEC).c -o $(EXEC) -lm

clean:
	$(RM) $(EXEC).o $(EXEC)
