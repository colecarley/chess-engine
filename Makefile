# set the compiler flags
CFLAGS := -std=c2x -Wall -Wextra -Werror -pedantic -g

chess: main.o board.o piece.o square.o game_info.o
	gcc -o chess main.o board.o piece.o square.o game_info.o $(CFLAGS)

board.o: board.c board.h
	gcc -c board.c $(CFLAGS)

piece.o: piece.c piece.h board.h
	gcc -c piece.c $(CFLAGS)

game_info.o: game_info.c game_info.h
	gcc -c game_info.c $(CFLAGS)

square.o: square.c square.h
	gcc -c square.c $(CFLAGS)

clean:
	rm -f *.o *.a *.so chess

