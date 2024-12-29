/*
** EPITECH PROJECT, 2024
** B-PSU-100-PAR-1-1-mytop-ariel.amriou
** File description:
** display.c
*/

#include "src.h"

void display(int offset)
{
    int lines = 0;
    int height = getmaxy(stdscr);

    first_line(&lines, height);
    second_line(&lines, height);
    lines++;
    if (lines < height) {
        printw("%%Cpu(s): 75.9 us, 16.7 sy, 6.4 ni, ");
        printw("0.7 id, 0.1 wa, 0.0 hi, 0.2 si, 0.0 st\n");
    }
    mem_swap_lines(&lines, height);
    display_tasks(&lines, height, offset);
}
