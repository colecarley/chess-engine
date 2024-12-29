#pragma once
#include "stdio.h"
#include "game_info.h"
#include "stdint.h"
#include "colors.h"

typedef uint64_t Bitboard;

struct Board
{
    Bitboard white_pawns;
    Bitboard white_knights;
    Bitboard white_bishops;
    Bitboard white_rooks;
    Bitboard white_queens;
    Bitboard white_king;
    Bitboard black_pawns;
    Bitboard black_knights;
    Bitboard black_bishops;
    Bitboard black_rooks;
    Bitboard black_queens;
    Bitboard black_king;

    Bitboard all_pieces;
    Bitboard white_pieces;
    Bitboard black_pieces;
} typedef Board;

void board_init(Board *b);
void board_free(Board *b);
void board_print(Board *b);
bool board_move_piece(Board *b, GameInfo *game_info, char from_file, int from_rank, char to_file, int to_rank);
void board_print_possible_moves(Board *b, GameInfo *game_info, char file, int rank);
