#pragma once
#include "piece.h"
#include "colors.h"

enum SquareType
{
    EMPTY,
    OCCUPIED
};

struct Square
{
    enum SquareType type;
    enum Color color;
    Piece piece;
} typedef Square;

void square_init(Square *s, enum SquareType type, enum Color color);
void square_set_piece(Square *s, Piece piece);
bool square_is_occupied(Square *s);
bool square_is_empty(Square *s);