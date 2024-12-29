# set the compiler flags
CFLAGS := -std=c2x -Wall -Wextra -Werror -g 

chess: main.o board.o game_info.o
	gcc -o chess main.o board.o game_info.o $(CFLAGS)

board.o: board.c board.h
	gcc -c board.c $(CFLAGS)

game_info.o: game_info.c game_info.h
	gcc -c game_info.c $(CFLAGS)

clean:
	rm -f *.o *.a *.so chess

