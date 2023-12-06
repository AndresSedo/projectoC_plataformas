CC=gcc
SRC=./proyecto1.c
SRC2=./proyecto2.c
SRC3=./proyecto3.c
EXE=exe
EXE2=exe
EXE3=exe


p1:
	$(CC) $(SRC) -lm -o $(EXE)
	./exe
p2:
	$(CC) $(SRC2) -lm -o $(EXE2)
	./exe
p3:
	$(CC) $(SRC3) -lm -o $(EXE3)
	./exe

