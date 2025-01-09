/*
** EPITECH PROJECT, 2024
** B-PSU-100-PAR-1-1-mytop-ariel.amriou
** File description:
** strcatpath.c
*/

#include "src.h"

char *strcatpath(char *foldername, char *pid, char *filename)
{
    int size = strlen(pid) + strlen(filename) + strlen(foldername) + 1;
    char *strpath = malloc(size);

    if (strpath == NULL)
        return NULL;
    strpath[size - 1] = '\0';
    strcpy(strpath, foldername);
    strpath = strcat(strpath, pid);
    strpath = strcat(strpath, filename);
    return strpath;
}
