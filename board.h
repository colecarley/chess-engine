#pragma once
#include "square.h"
#include "piece.h"
#include "stdio.h"

struct Board
{
    Square squares[8][8];
} typedef Board;

void board_init(Board *b);
void board_free(Board *b);
void board_print(Board *b);
void board_print_possible_moves(Board *b, int x, int y);
Square board_at(Board *b, int x, int y);