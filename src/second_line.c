/*
** EPITECH PROJECT, 2024
** B-PSU-100-PAR-1-1-mytop-ariel.amriou
** File description:
** second_line.c
*/

#include "src.h"

static void type_count(struct type *type, char c)
{
    type->total++;
    if (c == 'S' || c == 'I' || c == 'D')
        type->sleeping++;
    if (c == 'R' || c == 'X')
        type->running++;
    if (c == 'Z')
        type->zombie++;
    if (c == 'T')
        type->stopped++;
}

static void wich_type(char *filepath, struct type *type)
{
    int fd = open(filepath, O_RDONLY);
    char *buff = malloc(100);
    char *result;
    int nb = 0;

    free(filepath);
    nb = read(fd, buff, 100);
    if (nb == -1 || buff == NULL)
        return;
    for (int i = nb + 1; i < 100; i++)
        buff[i] = '\0';
    if (fd == -1)
        return;
    result = strstr(buff, "State") + 7;
    type_count(type, *result);
    close(fd);
    free(buff);
}

void second_line(int *lines, int height)
{
    DIR *dir = opendir("/proc/");
    struct dirent *info;
    struct type type = {0, 0, 0, 0, 0};

    if (dir == NULL)
        return;
    (*lines)++;
    if (*lines >= height) {
        closedir(dir);
        return;
    }
    info = readdir(dir);
    while (info != NULL) {
        if (isdigit(*info->d_name))
            wich_type(strcatpath("/proc/", info->d_name, "/status"), &type);
        info = readdir(dir);
    }
    printw("Tasks: %d total, %d running, %d sleeping, %d stopped, %d zombie\n",
        type.total, type.running, type.sleeping, type.stopped, type.zombie);
    closedir(dir);
}
