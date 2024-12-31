#pragma once
#include "common.h"

struct GameInfo
{
    bool white_turn;
    bool white_can_castle_kingside;
    bool white_can_castle_queenside;
    bool black_can_castle_kingside;
    bool black_can_castle_queenside;
} typedef GameInfo;

void game_info_init(GameInfo *g);
void game_info_switch_turn(GameInfo *g);
void game_info_set_white_can_castle_kingside(GameInfo *g, bool white_can_castle_kingside);
void game_info_set_white_can_castle_queenside(GameInfo *g, bool white_can_castle_queenside);
void game_info_set_black_can_castle_kingside(GameInfo *g, bool black_can_castle_kingside);
void game_info_set_black_can_castle_queenside(GameInfo *g, bool black_can_castle_queenside);