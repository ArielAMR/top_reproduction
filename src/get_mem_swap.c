/*
** EPITECH PROJECT, 2024
** B-PSU-100-PAR-1-1-mytop-ariel.amriou
** File description:
** get_mem_swap.c
*/

#include "src.h"

float get_mem_swap(char const *delim, char *buff)
{
    char *tmp = strstr(buff, delim);

    strtok(tmp, " ");
    tmp = strtok(NULL, " ");
    return atoi(tmp) / MEBIBIT;
}
