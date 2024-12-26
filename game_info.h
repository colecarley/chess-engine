#pragma once
#include "common.h"

struct GameInfo
{
    bool white_turn;
} typedef GameInfo;

void game_info_init(GameInfo *g);
void game_info_switch_turn(GameInfo *g);
bool game_info_is_white_turn(GameInfo *g);
