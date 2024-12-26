#include "square.h"

void square_init(Square *s, enum SquareType type, enum Color color)
{
    s->type = type;
    s->color = color;
}

void square_set_piece(Square *s, Piece piece)
{
    s->piece = piece;
}

bool square_is_occupied(Square *s)
{
    return s->type == OCCUPIED;
}

bool square_is_empty(Square *s)
{
    return s->type == EMPTY;
}
