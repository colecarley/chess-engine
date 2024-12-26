#include "vector.h"
#include "board.h"

void print_menu()
{
    printf("Enter move (e.g. 0,0):\n");
    printf("(9 to exit)\n");
}

void handle_scan_error(int scan_result)
{
    if (scan_result <= 0)
    {
        printf("Invalid input\n");

        // Clear the input buffer
        while (getchar() != '\n')
            ;
    }
}

int main()
{
    Board board;
    board_init(&board);

    while (true)
    {
        board_print(&board);
        print_menu();
        int row = 0, col = 0;
        handle_scan_error(scanf("%d, %d", &row, &col));

        if (row == 9 || col == 9)
            return 0;

        board_print_possible_moves(&board, row, col);
    }

    board_free(&board);
    return 0;
}
