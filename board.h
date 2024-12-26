#pragma once
#include "square.h"
#include "piece.h"
#include "stdio.h"
#include "game_info.h"

struct Board
{
    Square squares[8][8];
} typedef Board;

void board_init(Board *b);
void board_free(Board *b);
void board_print(Board *b);
void board_print_possible_moves(Board *b, GameInfo *game_info, int x, int y);
bool board_move_piece(Board *b, GameInfo *game_info, int row, int col, int new_row, int new_col);
Square *board_at(Board *b, int x, int y);
