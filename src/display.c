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
    mem_swap_lines(&lines, height);
    display_tasks(&lines, height, offset);
}
