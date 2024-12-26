chess: main.o board.o piece.o square.o
	gcc -o chess main.o board.o piece.o square.o

board.o: board.c board.h
	gcc -c board.c

piece.o: piece.c piece.h board.h
	gcc -c piece.c

square.o: square.c square.h
	gcc -c square.c

clean:
	rm -f *.o *.a *.so chess

