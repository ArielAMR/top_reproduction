/*
** EPITECH PROJECT, 2024
** B-PSU-100-PAR-1-1-mytop-ariel.amriou
** File description:
** getinstat.c
*/

#include "src.h"

static int populate_list_stat(char *tmp, char *list_stats[], int i, char *buff)
{
    tmp = strtok(buff, " ");
    if (tmp == NULL)
        return 1;
    list_stats[i] = strdup(tmp);
    return 0;
}

static void getpr(struct linked_list_s *head, char *list_stats[])
{
    head->priority = strdup(list_stats[17]);
    if (!strcmp(head->priority, "-100"))
        strcpy(head->priority, "rt");
}

static void get_time_s(struct linked_list_s *head,
    char *utime_s, char *ctime_s)
{
    long long int time_s_i = atoll(utime_s) + atoll(ctime_s);

    head->time_s.minutes = time_s_i / 6000;
    head->time_s.fseconds = time_s_i % 6000 / 100.0;
}

static int parsestat(char *list_stats[], int nbvalues, char *buff, int fd)
{
    char *tmp = NULL;

    if (populate_list_stat(tmp, list_stats, 0, buff))
        return free_list_stat(1, list_stats, fd);
    for (int i = 1; i < nbvalues; i++)
        if (populate_list_stat(tmp, list_stats, i, NULL))
            return free_list_stat(i, list_stats, fd);
    return 0;
}

int getinstat(struct linked_list_s *head)
{
    int nbvalues = 19;
    char *path = strcatpath("/proc/", head->pid, "/stat");
    int fd = open(path, O_RDONLY);
    char *list_stats[nbvalues];
    char buff[STATREAD] = {0};

    free(path);
    if (fd == -1 || path == NULL || read(fd, buff, STATREAD) == -1 ||
        parsestat(list_stats, nbvalues, buff, fd) == 84)
        return 84;
    getpr(head, list_stats);
    head->nice = strdup(list_stats[18]);
    get_time_s(head, list_stats[13], list_stats[14]);
    free_list_stat(nbvalues, list_stats, fd);
    close(fd);
    return 0;
}
