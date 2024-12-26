#include "game_info.h"

void game_info_init(GameInfo *g)
{
    g->white_turn = true;
}

void game_info_switch_turn(GameInfo *g)
{
    g->white_turn = !g->white_turn;
}

bool game_info_is_white_turn(GameInfo *g)
{
    return g->white_turn;
}