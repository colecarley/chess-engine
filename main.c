#include "board.h"
#include "game_info.h"
#include "common.h"

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

int main()
{
    Board board;
    GameInfo game_info;
    board_init(&board);
    game_info_init(&game_info);
    bool clear = true;
    while (true)
    {
        if (clear)
        {
            printf("\033[2J\033[1;1H");
            board_print(&board);
        }
        printf(">");
        char *buf = malloc(MAX_CHARACTERS);
        fgets(buf, MAX_CHARACTERS, stdin);

        if (buf[0] == 'q')
            break;

        char file;
        int rank;
        if (buf[0] == 's')
        {
            if (is_scan_error(sscanf(buf, "s %c%d", &file, &rank)))
            {
                continue;
            }
            clear = false;

            board_print_possible_moves(&board, &game_info, file, rank);
        }
        else
        {
            char new_file;
            int new_rank;
            if (is_scan_error(sscanf(buf, "%c%d%c%d", &file, &rank, &new_file, &new_rank)))
            {
                continue;
            }

            if (board_move_piece(&board, &game_info, file, rank, new_file, new_rank))
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
