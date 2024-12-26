chess: main.o board.o piece.o square.o game_info.o
	gcc -o chess main.o board.o piece.o square.o game_info.o

board.o: board.c board.h
	gcc -c board.c

piece.o: piece.c piece.h board.h
	gcc -c piece.c

game_info.o: game_info.c game_info.h
	gcc -c game_info.c

square.o: square.c square.h
	gcc -c square.c

clean:
	rm -f *.o *.a *.so chess

