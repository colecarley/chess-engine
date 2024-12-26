#include "board.h"

static enum PieceType starting_row[8] = {ROOK,
                                         KNIGHT,
                                         BISHOP,
                                         QUEEN,
                                         KING,
                                         BISHOP,
                                         KNIGHT,
                                         ROOK};

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
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j == 0)
            {
                printf("+--+");
            }
            else
            {
                printf("--+");
            }
        }

        printf("\n");
        for (int j = 0; j < 8; j++)
        {
            if (j == 0)
            {
                printf("|");
            }
            printf("%c ", b->squares[i][j].type == EMPTY ? ' ' : piece_get_name(b->squares[i][j].piece));
            printf("|");
        }
        printf("\n");
    }
    for (int j = 0; j < 8; j++)
    {
        if (j == 0)
        {
            printf("+--+");
        }
        else
        {
            printf("--+");
        }
    }
    printf("\n");
}

void board_free(Board *b)
{
    board_init(b);
}

void board_print_possible_moves(Board *b, int x, int y)
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

    piece_print_possible_moves(&s.piece, b, x, y);
}

Square board_at(Board *b, int x, int y)
{
    return b->squares[x][y];
}