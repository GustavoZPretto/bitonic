# FLAGS=-O3
#
# CC=icc
# 
# RM=rm -f
# 
# EXEC=bitonic
# 
# all: $(EXEC)
# 
# $(EXEC):
# 	$(CC) $(FLAGS) $(EXEC).cc -c -o $(EXEC).o
# 	$(CC) $(FLAGS) $(EXEC).o -o $(EXEC)
# 
# clean:
# 	$(RM) $(EXEC).o $(EXEC)

FLAGS=-O3

CC=gcc

RM=rm -f

EXEC=bitonic

all: $(EXEC)

$(EXEC): $(EXEC).c
	$(CC) $(FLAGS) $(EXEC).c -o $(EXEC) -lm

clean:
	$(RM) $(EXEC).o $(EXEC)

