FLAGS=-fopenmp #-O3 # adicionado -fopenmp pra rodar openmp e -lm pq tava bugado

CC=gcc # adicionei gcc pra rodar no nosso pczinho
#CC=icc # intel noggers descomentar para rodar la no pczao

RM=rm -f

EXEC=bitonic

all: $(EXEC)

# alterei essa bagaca pq tava bugado
# tive que adicionar -lm aqui tb pq tava dando erro
$(EXEC): $(EXEC).c
	$(CC) $(FLAGS) $(EXEC).c -o $(EXEC) -lm

clean:
	$(RM) $(EXEC).o $(EXEC)
