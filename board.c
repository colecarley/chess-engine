#include "board.h"
#include "piece_types.h"
#include "math.h"
#include "stdint.h"
#include "stdio.h"

#define DISPLAY_WIDTH 19
#define DISPLAY_HEIGHT 12
#define BIT_POS(__a) __builtin_ctzll(__a)
#define UNUSED(x) (void)(x)

static Bitboard pawn_row = 0b11111111;
static Bitboard knight_row = 0b01000010;
static Bitboard bishop_row = 0b00100100;
static Bitboard rook_row = 0b10000001;
static Bitboard queen_row = 0b00001000;
static Bitboard king_row = 0b00010000;

// static void print_bits(Bitboard bb)
// {
//     for (int i = 0; i < 64; i++)
//     {
//         printf("%lld", (bb >> i) & 1);
//         if (i % 8 == 7)
//         {
//             printf("\n");
//         }
//     }
//

void board_upate_all_pieces(Board *b)
{
    b->white_pieces = b->white_pawns |
                      b->white_bishops |
                      b->white_knights |
                      b->white_rooks |
                      b->white_queens |
                      b->white_king;

    b->black_pieces = b->black_pawns |
                      b->black_bishops |
                      b->black_knights |
                      b->black_rooks |
                      b->black_queens |
                      b->black_king;

    b->all_pieces = b->white_pieces | b->black_pieces;
}

void board_init(Board *b)
{
    b->white_pawns = pawn_row << 8;
    b->white_bishops = bishop_row;
    b->white_knights = knight_row;
    b->white_rooks = rook_row;
    b->white_queens = queen_row;
    b->white_king = king_row;

    b->black_pawns = pawn_row << 48;
    b->black_bishops = bishop_row << 56;
    b->black_knights = knight_row << 56;
    b->black_rooks = rook_row << 56;
    b->black_queens = queen_row << 56;
    b->black_king = king_row << 56;

    board_upate_all_pieces(b);
}

void board_print(Board *b)
{
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            Bitboard mask = 1LL << (i * 8 + j);
            if (b->white_pawns & mask)
                printf("P ");
            else if (b->white_knights & mask)
                printf("N ");
            else if (b->white_bishops & mask)
                printf("B ");
            else if (b->white_rooks & mask)
                printf("R ");
            else if (b->white_queens & mask)
                printf("Q ");
            else if (b->white_king & mask)
                printf("K ");
            else if (b->black_pawns & mask)
                printf("p ");
            else if (b->black_knights & mask)
                printf("n ");
            else if (b->black_bishops & mask)
                printf("b ");
            else if (b->black_rooks & mask)
                printf("r ");
            else if (b->black_queens & mask)
                printf("q ");
            else if (b->black_king & mask)
                printf("k ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

void board_free(Board *b)
{
    board_init(b);
}

static Bitboard coord_to_bitboard(char file, int rank)
{
    if (file >= 'a' && file <= 'h')
        file -= 'a' - 1;

    int y = file - 'A';
    int x = rank - 1;
    return (Bitboard)1 << (x * 8 + y);
}

static bool piece_at(Board *b, Bitboard bb)
{
    return b->all_pieces & bb;
}

static enum Color get_piece_color(Board *b, Bitboard bb)
{
    if (b->white_pieces & bb)
        return WHITE;
    else if (b->black_pieces & bb)
        return BLACK;

    printf("ERROR: piece not found\n");
    exit(1);
}

static enum PieceType get_piece_type(Board *b, Bitboard bb)
{
    if ((b->white_pawns | b->black_pawns) & bb)
        return PAWN;
    else if ((b->white_knights | b->black_knights) & bb)
        return KNIGHT;
    else if ((b->white_bishops | b->black_bishops) & bb)
        return BISHOP;
    else if ((b->white_rooks | b->black_rooks) & bb)
        return ROOK;
    else if ((b->white_queens | b->black_queens) & bb)
        return QUEEN;
    else if ((b->white_king | b->black_king) & bb)
        return KING;

    printf("ERROR: piece not found\n");
    exit(1);
}

static void move_white_pawn(Board *b, Bitboard from, Bitboard to)
{
    b->white_pawns = (b->white_pawns & ~from) | to;
}

static void move_white_knight(Board *b, Bitboard from, Bitboard to)
{
    b->white_knights = (b->white_knights & ~from) | to;
}

static void move_white_bishop(Board *b, Bitboard from, Bitboard to)
{
    b->white_bishops = (b->white_bishops & ~from) | to;
}

static void move_white_rook(Board *b, Bitboard from, Bitboard to)
{
    b->white_rooks = (b->white_rooks & ~from) | to;
}

static void move_white_queen(Board *b, Bitboard from, Bitboard to)
{
    b->white_queens = (b->white_queens & ~from) | to;
}

static void move_white_king(Board *b, Bitboard from, Bitboard to)
{
    b->white_king = (b->white_king & ~from) | to;
}

static void move_black_pawn(Board *b, Bitboard from, Bitboard to)
{
    b->black_pawns = (b->black_pawns & ~from) | to;
}

static void move_black_knight(Board *b, Bitboard from, Bitboard to)
{
    b->black_knights = (b->black_knights & ~from) | to;
}

static void move_black_bishop(Board *b, Bitboard from, Bitboard to)
{
    b->black_bishops = (b->black_bishops & ~from) | to;
}

static void move_black_rook(Board *b, Bitboard from, Bitboard to)
{
    b->black_rooks = (b->black_rooks & ~from) | to;
}

static void move_black_queen(Board *b, Bitboard from, Bitboard to)
{
    b->black_queens = (b->black_queens & ~from) | to;
}

static void move_black_king(Board *b, Bitboard from, Bitboard to)
{
    b->black_king = (b->black_king & ~from) | to;
}

typedef void (*MoveFunc)(Board *b, Bitboard from, Bitboard to);
static MoveFunc move_map[2][6] = {
    {move_white_pawn, move_white_knight, move_white_bishop, move_white_rook, move_white_queen, move_white_king},
    {move_black_pawn, move_black_knight, move_black_bishop, move_black_rook, move_black_queen, move_black_king}};

static bool is_valid_pawn_move(Board *b, Bitboard from, Bitboard to)
{
    UNUSED(b);
    uint8_t from_pos = BIT_POS(from);
    uint8_t to_pos = BIT_POS(to);
    uint8_t diff = abs(from_pos - to_pos);

    if (diff == 8)
    {
        if (b->white_pieces & from)
            return from < to;
        else
            return from > to;
    }

    if (diff == 16)
    {
        if (b->white_pieces & from && from & pawn_row << 8)
        {
            return from < to;
        }
        else if (from & pawn_row << 48)
        {
            return from > to;
        }
        return false;
    }

    if (diff == 7 || diff == 9)
    {
        // TODO: en passant
        if (b->white_pieces & from)
            return from < to && b->black_pieces & to;
        else
            return from > to && b->white_pieces & to;
    }

    return false;
}

static bool is_valid_knight_move(Board *b, Bitboard from, Bitboard to)
{
    UNUSED(b);
    uint8_t from_pos = BIT_POS(from);
    uint8_t to_pos = BIT_POS(to);
    uint8_t diff = abs(from_pos - to_pos);

    if (diff == 6 || diff == 10)
        return from_pos % 8 + 2 == to_pos % 8 || from_pos % 8 - 2 == to_pos % 8;
    else if (diff == 15 || diff == 17)
        return from_pos % 8 + 1 == to_pos % 8 || from_pos % 8 - 1 == to_pos % 8;

    return false;
}

static bool is_piece_higher(Board *b, Bitboard from, uint8_t diff, int factor)
{
    for (int i = 1; i < diff; i++)
        if (b->all_pieces & (from >> i * factor))
            return false;
    return true;
}

static bool is_piece_lower(Board *b, Bitboard from, uint8_t diff, int factor)
{
    for (int i = 1; i < diff / factor; i++)
        if (b->all_pieces & (from << i * factor))
            return false;
    return true;
}

static bool is_valid_bishop_move(Board *b, Bitboard from, Bitboard to)
{
    UNUSED(b);
    uint8_t from_pos = BIT_POS(from);
    uint8_t to_pos = BIT_POS(to);
    uint8_t diff = abs(from_pos - to_pos);

    if (diff % 7 == 0)
    {
        if (from < to)
            return is_piece_higher(b, from, diff / 7, 7);
        return is_piece_lower(b, from, diff / 7, 7);
    }

    if (diff % 9 == 0)
    {
        if (from < to) // moving up
            return is_piece_higher(b, from, diff / 9, 9);
        return is_piece_lower(b, from, diff / 9, 9);
    }

    return false;
}

static bool is_valid_rook_move(Board *b, Bitboard from, Bitboard to)
{
    uint8_t from_pos = BIT_POS(from);
    uint8_t to_pos = BIT_POS(to);
    uint8_t diff = abs(from_pos - to_pos);

    if (diff % 8 == 0)
    {
        if (from_pos % 8 != to_pos % 8)
            return false;

        if (from > to) // moving up
            return is_piece_higher(b, from, diff / 8, 8);
        return is_piece_lower(b, from, diff / 8, 8);
    }

    if (diff < 8)
    {
        if (from_pos / 8 != to_pos / 8)
            return false;

        if (from > to) // moving left
            return is_piece_higher(b, from, diff, 1);
        return is_piece_lower(b, from, diff, 1);
    }

    return false;
}

static bool is_valid_queen_move(Board *b, Bitboard from, Bitboard to)
{
    return is_valid_bishop_move(b, from, to) || is_valid_rook_move(b, from, to);
}

static uint8_t valid_king_moves[8] = {1, 7, 8, 9, -1, -7, -8, -9};
static bool is_valid_king_move(Board *b, Bitboard from, Bitboard to)
{
    UNUSED(b);
    uint8_t from_pos = BIT_POS(from);
    uint8_t to_pos = BIT_POS(to);
    uint8_t diff = abs(from_pos - to_pos);

    for (int i = 0; i < 8; i++)
        if (diff == valid_king_moves[i])
            return true;

    return false;
}

typedef bool (*ValidMoveFunc)(Board *b, Bitboard from, Bitboard to);
static ValidMoveFunc valid_move_map[6] = {
    is_valid_pawn_move,
    is_valid_knight_move,
    is_valid_bishop_move,
    is_valid_rook_move,
    is_valid_queen_move,
    is_valid_king_move};

static bool is_valid_move(Board *b, GameInfo *game_info, Bitboard from, Bitboard to)
{
    if (game_info_is_white_turn(game_info) && !(b->white_pieces & from))
        return false;

    if (!piece_at(b, from))
        return false;

    if (piece_at(b, to) && get_piece_color(b, from) == get_piece_color(b, to))
    {
        return false;
    }

    return valid_move_map[get_piece_type(b, from)](b, from, to);
}

bool board_move_piece(Board *b, GameInfo *game_info, char from_file, int from_rank, char to_file, int to_rank)
{
    Bitboard from = coord_to_bitboard(from_file, from_rank);
    Bitboard to = coord_to_bitboard(to_file, to_rank);

    bool occupied = b->all_pieces & from;
    if (!occupied)
        return false;

    if (!is_valid_move(b, game_info, from, to))
    {
        printf("INVALID MOVE\n");
        return false;
    }

    move_map[get_piece_color(b, from)][get_piece_type(b, from)](b, from, to);

    board_upate_all_pieces(b);
    return true;
}

void board_print_possible_moves(Board *b, GameInfo *game_info, char file, int rank)
{
    UNUSED(game_info);
    Bitboard from = coord_to_bitboard(file, rank);
    ValidMoveFunc predicate = valid_move_map[get_piece_type(b, from)];
    int count = 0;
    for (int i = 0; i < 64; i++)
    {
        Bitboard to = (Bitboard)1 << i;
        if (!piece_at(b, from))
            continue;

        if (piece_at(b, to) && get_piece_color(b, from) == get_piece_color(b, to))
            continue;

        if (predicate(b, from, (Bitboard)1 << i))
        {
            printf("%d. %c%d ", ++count, 'A' + i % 8, i / 8 + 1);
        }
    }

    if (count == 0)
        printf("No possible moves\n");
    else
        printf("\n");
}