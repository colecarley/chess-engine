#include "vector.h"
#include "board.h"
#include "game_info.h"

#define MAX_CHARACTERS 100

bool is_scan_error(int scan_result)
{
    if (scan_result <= 0)
    {
        printf("Invalid input\n");

        // Clear the input buffer
        while (getchar() != '\n')
            ;
    }

    return scan_result <= 0;
}

void get_coordinates(int *row, int *col, char file, int rank)
{
    *row = rank - 1;
    *col = file - 'A';
}

int main()
{
    Board board;
    GameInfo game_info;
    board_init(&board);
    bool clear = true;
    while (true)
    {
        if (clear)
        {
            printf("\033[2J\033[1;1H");
            board_print(&board);
        }
        printf(">");
        char *buf;
        fgets(buf, MAX_CHARACTERS, stdin);

        if (buf[0] == 'q')
            break;

        char file;
        int rank;
        int row, col;
        if (buf[0] == 's')
        {
            if (is_scan_error(sscanf(buf, "s %c%d", &file, &rank)))
            {
                continue;
            }

            get_coordinates(&row, &col, file, rank);
            board_print_possible_moves(&board, &game_info, row, col);
        }
        else
        {
            char new_file;
            int new_rank;
            int new_row, new_col;
            if (is_scan_error(sscanf(buf, "%c%d%c%d", &file, &rank, &new_file, &new_rank)))
            {
                continue;
            }

            get_coordinates(&row, &col, file, rank);
            get_coordinates(&new_row, &new_col, new_file, new_rank);
            if (board_move_piece(&board, &game_info, row, col, new_row, new_col))
            {
                game_info_switch_turn(&game_info);
                clear = true;
            }
            else
            {
                clear = false;
            }
        }
    }

    board_free(&board);
    return 0;
}
