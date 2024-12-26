#include "board.h"

#define DISPLAY_WIDTH 19
#define DISPLAY_HEIGHT 12

const char *x_coordinates = "   A B C D E F G H   ";
const char *y_coordinates = "87654321";

static enum PieceType starting_row[8] = {ROOK,
                                         KNIGHT,
                                         BISHOP,
                                         QUEEN,
                                         KING,
                                         BISHOP,
                                         KNIGHT,
                                         ROOK};

static void print_x_coordinates()
{
    for (int i = 0; i < DISPLAY_WIDTH; i++)
    {
        printf("%c", x_coordinates[i]);
    }
    printf("\n");
}

void board_init(Board *b)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            square_init(&b->squares[i][j], EMPTY, i % 2 == 0 ? WHITE : BLACK);
        }
    }

    for (int i = 0; i < 8; i++)
    {
        square_init(&b->squares[0][i], OCCUPIED, WHITE);
        square_set_piece(&b->squares[0][i], (Piece){starting_row[i], WHITE});

        square_init(&b->squares[1][i], OCCUPIED, WHITE);
        square_set_piece(&b->squares[1][i], (Piece){PAWN, WHITE});

        square_init(&b->squares[6][i], OCCUPIED, BLACK);
        square_set_piece(&b->squares[6][i], (Piece){PAWN, BLACK});

        square_init(&b->squares[7][i], OCCUPIED, BLACK);
        square_set_piece(&b->squares[7][i], (Piece){starting_row[i], BLACK});
    }
}

void board_print(Board *b)
{
    print_x_coordinates();
    printf("\n");
    for (int i = 7; i >= 0; i--)
    {
        printf("%c  ", y_coordinates[7 - i]);
        for (int j = 0; j < 8; j++)
        {
            printf("%c ", b->squares[i][j].type == EMPTY ? '.' : piece_get_name(b->squares[i][j].piece));
        }
        printf(" %c\n", y_coordinates[7 - i]);
    }
    printf("\n");
    print_x_coordinates();
}

void board_free(Board *b)
{
    board_init(b);
}

void board_print_possible_moves(Board *b, GameInfo *game_info, int x, int y)
{
    Square s = b->squares[x][y];
    if (s.type == EMPTY)
    {
        printf("No piece in this square\n");
        return;
    }

    switch (s.piece.type)
    {
    case PAWN:
        printf("Pawn\n");
        break;
    case KNIGHT:
        printf("Knight\n");
        break;
    case BISHOP:
        printf("Bishop\n");
        break;
    case ROOK:
        printf("Rook\n");
        break;
    case QUEEN:
        printf("Queen\n");
        break;
    case KING:
        printf("King\n");
        break;
    default:
        printf("Invalid piece\n");
        return;
    }

    piece_print_possible_moves(&s.piece, b, game_info, x, y);
}

Square *board_at(Board *b, int x, int y)
{
    return &b->squares[x][y];
}

bool board_move_piece(Board *b, GameInfo *game_info, int row, int col, int new_row, int new_col)
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8 || new_row < 0 || new_row >= 8 || new_col < 0 || new_col >= 8)
    {
        printf("Invalid move\n");
        return false;
    }

    Square *s = board_at(b, row, col);
    if (square_is_empty(s))
    {
        printf("No piece in this square\n");
        return false;
    }

    if (game_info_is_white_turn(game_info) && s->piece.color == BLACK)
    {
        printf("It's white's turn, cannot move black's piece\n");
        return false;
    }
    else if (!game_info_is_white_turn(game_info) && s->piece.color == WHITE)
    {
        printf("It's black's turn, cannot move white's piece\n");
        return false;
    }

    if (!piece_move_is_valid(&s->piece, b, game_info, row, col, new_row, new_col))
    {
        printf("Invalid move\n");
        return false;
    }

    s->type = EMPTY;

    Square *new_s = board_at(b, new_row, new_col);
    new_s->type = OCCUPIED;
    new_s->piece = s->piece;
    return true;
}
