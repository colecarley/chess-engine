#include "piece.h"
#include "board.h"
#include "common.h"

#define MAX_MOVES 64
#define PAWN_MOVES 4
#define KNIGHT_MOVES 8
#define BISHOP_MOVES 4
#define ROOK_MOVES 4
#define QUEEN_MOVES 8
#define KING_MOVES 8

static Move *generate_moves(Piece *p, struct Board *b, MoveDescription *move_descriptions, int moves_length, int row, int col, int *moves_count);

char piece_get_name(Piece piece)
{
    switch (piece.type)
    {
    case PAWN:
        return piece.color == WHITE ? 'P' : 'p';
    case KNIGHT:
        return piece.color == WHITE ? 'N' : 'n';
    case BISHOP:
        return piece.color == WHITE ? 'B' : 'b';
    case ROOK:
        return piece.color == WHITE ? 'R' : 'r';
    case QUEEN:
        return piece.color == WHITE ? 'Q' : 'q';
    case KING:
        return piece.color == WHITE ? 'K' : 'k';
    default:
        return ' ';
    }
}

static MoveDescription white_pawn_moves[PAWN_MOVES] = {
    {1, 0, 1, false},
    {1, 1, 1, true},  // must capture
    {1, -1, 1, true}, // must capture
    {2, 0, 1, false}};

static MoveDescription black_pawn_moves[PAWN_MOVES] = {
    {-1, 0, 1, false},
    {-1, 1, 1, true},  // must capture
    {-1, -1, 1, true}, // must capture
    {-2, 0, 1, false}};

static MoveDescription knight_moves[KNIGHT_MOVES] = {
    {1, 2, 1, true},
    {1, -2, 1, true},
    {-1, 2, 1, true},
    {-1, -2, 1, true},
    {2, 1, 1, true},
    {2, -1, 1, true},
    {-2, 1, 1, true},
    {-2, -1, 1, true}};

static MoveDescription bishop_moves[BISHOP_MOVES] = {
    {1, 1, 8, true},
    {1, -1, 8, true},
    {-1, 1, 8, true},
    {-1, -1, 8, true}};

static MoveDescription rook_moves[ROOK_MOVES] = {
    {1, 0, 8, true},
    {-1, 0, 8, true},
    {0, 1, 8, true},
    {0, -1, 8, true}};

static MoveDescription queen_moves[QUEEN_MOVES] = {
    {1, 0, 8, true},
    {-1, 0, 8, true},
    {0, 1, 8, true},
    {0, -1, 8, true},
    {1, 1, 8, true},
    {1, -1, 8, true},
    {-1, 1, 8, true},
    {-1, -1, 8, true}};

static MoveDescription king_moves[KING_MOVES] = {
    {1, 0, 1, true},
    {-1, 0, 1, true},
    {0, 1, 1, true},
    {0, -1, 1, true},
    {1, 1, 1, true},
    {1, -1, 1, true},
    {-1, 1, 1, true},
    {-1, -1, 1, true}};

static void get_file_and_rank(char *file, int *rank, int col, int row)
{
    *file = col + 'A';
    *rank = row + 1;
}

void piece_print_possible_moves(Piece *p, struct Board *b, GameInfo *game_info, int row, int col)
{
    Move *moves;
    int moves_count = 0;
    switch (p->type)
    {
    case PAWN:
        moves = generate_moves(p, b, game_info_is_white_turn(game_info) ? white_pawn_moves : black_pawn_moves, PAWN_MOVES, row, col, &moves_count);
        break;
    case KNIGHT:
        moves = generate_moves(p, b, knight_moves, KNIGHT_MOVES, row, col, &moves_count);
        break;
    case BISHOP:
        moves = generate_moves(p, b, bishop_moves, BISHOP_MOVES, row, col, &moves_count);
        break;
    case ROOK:
        moves = generate_moves(p, b, rook_moves, ROOK_MOVES, row, col, &moves_count);
        break;
    case QUEEN:
        moves = generate_moves(p, b, queen_moves, QUEEN_MOVES, row, col, &moves_count);
        break;
    case KING:
        moves = generate_moves(p, b, king_moves, KING_MOVES, row, col, &moves_count);
        break;
    default:
        printf("Invalid piece type\n");
        exit(1);
        return;
    }

    for (int i = 0; i < moves_count; i++)
    {
        if (moves[i].capture)
        {
            printf("Capture %c: %c%d\n", piece_get_name(board_at(b, moves[i].file, moves[i].rank)->piece), moves[i].file, moves[i].rank);
        }
        else
        {
            printf("Move: %c%d\n", moves[i].file, moves[i].rank);
        }
    }

    free(moves);
}

static Move *generate_moves(Piece *p, struct Board *b, MoveDescription *move_descriptions, int moves_length, int row, int col, int *moves_count)
{
    Move *possible_moves = malloc(sizeof(Move) * MAX_MOVES);
    int possible_moves_count = 0;
    for (int i = 0; i < moves_length; i++)
    {
        for (int j = 1; j <= move_descriptions[1].steps; j++)
        {
            int new_row = row + (move_descriptions[i].row * j);
            int new_col = col + (move_descriptions[i].col * j);

            int rank;
            char file;
            get_file_and_rank(&file, &rank, new_col, new_row);

            if (new_row < 0 || new_row >= 8 || new_col < 0 || new_col >= 8)
            {
                break;
            }

            Square *s = board_at(b, new_row, new_col);
            if (square_is_occupied(s))
            {
                if (s->piece.color != p->color && move_descriptions[i].can_capture)
                {
                    possible_moves[possible_moves_count++] = (Move){
                        rank,
                        file,
                        new_row,
                        new_col,
                        .capture = true};
                }
                break;
            }

            possible_moves[possible_moves_count++] = (Move){
                rank,
                file,
                new_row,
                new_col,
                .capture = false};
        }
    }

    *moves_count = possible_moves_count;
    return possible_moves;
}

bool piece_move_is_valid(Piece *p, Board *b, GameInfo *game_info, int row, int col, int new_row, int new_col)
{
    Move *moves;
    int moves_count = 0;
    switch (p->type)
    {
    case PAWN:
        moves = generate_moves(p, b, game_info_is_white_turn(game_info) ? white_pawn_moves : black_pawn_moves, PAWN_MOVES, row, col, &moves_count);
        break;
    case KNIGHT:
        moves = generate_moves(p, b, knight_moves, KNIGHT_MOVES, row, col, &moves_count);
        break;
    case BISHOP:
        moves = generate_moves(p, b, bishop_moves, BISHOP_MOVES, row, col, &moves_count);
        break;
    case ROOK:
        moves = generate_moves(p, b, rook_moves, ROOK_MOVES, row, col, &moves_count);
        break;
    case QUEEN:
        moves = generate_moves(p, b, queen_moves, QUEEN_MOVES, row, col, &moves_count);
        break;
    case KING:
        moves = generate_moves(p, b, king_moves, KING_MOVES, row, col, &moves_count);
        break;
    default:
        return false;
    }

    for (int i = 0; i < moves_count; i++)
    {
        if (moves[i].row == new_row && moves[i].col == new_col)
        {
            free(moves);
            return true;
        }
    }

    free(moves);
    return false;
}
