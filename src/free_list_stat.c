/*
** EPITECH PROJECT, 2024
** B-PSU-100-PAR-1-1-mytop-ariel.amriou
** File description:
** free_list_stat.c
*/

#include "src.h"

int free_list_stat(int nbvalues, char *list_stats[], int fd)
{
    for (int i = 0; i < nbvalues; i++)
        free(list_stats[i]);
    close(fd);
    return 84;
}
