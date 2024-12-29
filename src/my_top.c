/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main function
*/

#include "src.h"

void init(void)
{
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    cbreak();
    noecho();
    attron(COLOR_PAIR(1));
    timeout(3000);
}

int scr(void)
{
    char input = 0;
    int offset = 0;

    while (input != 'q') {
        if (input == 'B')
            offset++;
        if (input == 'A' && offset > 0)
            offset--;
        if (input == '~' && offset > 0)
            offset -= 10;
        clear();
        display(offset);
        refresh();
        input = getch();
    }
    return 0;
}

int my_top(void)
{
    init();
    scr();
    endwin();
    return 0;
}

int main(void)
{
    return my_top();
}
