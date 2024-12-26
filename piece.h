#pragma once
#include "colors.h"
#include "common.h"
#include "game_info.h"

enum PieceType
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

struct MoveDescription
{
    int row;
    int col;
    int steps;
    bool can_capture;
} typedef MoveDescription;

struct Move
{
    int rank;
    char file;
    int row;
    int col;
    bool capture;
} typedef Move;

struct Piece
{
    enum PieceType type;
    enum Color color;
    bool can_jump;
} typedef Piece;

char piece_get_name(Piece piece);

struct Board;
void piece_print_possible_moves(Piece *p, struct Board *b, GameInfo *game_info, int row, int col);
static Move *generate_moves(Piece *p, struct Board *b, MoveDescription *moves, int moves_length, int row, int col, int *moves_count);
bool piece_move_is_valid(Piece *p, struct Board *b, GameInfo *game_info, int row, int col, int new_row, int new_col);