NAME=tralloc
INC=$(NAME).h
SRC=$(NAME).c
OBJ=$(NAME).o
CFLAGS=-Wall -ansi -pedantic

all:
	${CC} $(CFLAGS) -c $(SRC)
	ar -rc $(NAME).a $(OBJ)

test:
	rm -f test
	${CC} -Wall -pedantic -g -o test test.c tralloc.c
	@./test

clean:
	rm -f $(NAME).a $(OBJ) test

