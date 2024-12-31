#include "game_info.h"

void game_info_init(GameInfo *g)
{
    g->white_turn = true;
    g->white_can_castle_kingside = true;
    g->white_can_castle_queenside = true;
    g->black_can_castle_kingside = true;
    g->black_can_castle_queenside = true;
}

void game_info_switch_turn(GameInfo *g)
{
    g->white_turn = !g->white_turn;
}

bool game_info_is_white_turn(GameInfo *g)
{
    return g->white_turn;
}

void game_info_set_white_can_castle_kingside(GameInfo *g, bool white_can_castle_kingside)
{
    g->white_can_castle_kingside = white_can_castle_kingside;
}

void game_info_set_white_can_castle_queenside(GameInfo *g, bool white_can_castle_queenside)
{
    g->white_can_castle_queenside = white_can_castle_queenside;
}

void game_info_set_black_can_castle_kingside(GameInfo *g, bool black_can_castle_kingside)
{
    g->black_can_castle_kingside = black_can_castle_kingside;
}

void game_info_set_black_can_castle_queenside(GameInfo *g, bool black_can_castle_queenside)
{
    g->black_can_castle_queenside = black_can_castle_queenside;
}
