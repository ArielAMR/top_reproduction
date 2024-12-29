/*
** EPITECH PROJECT, 2024
** B-PSU-100-PAR-1-1-mytop-ariel.amriou
** File description:
** first_line.c
*/

#include "src.h"

static void get_nbr_usr(void)
{
    int fd = open("/var/run/utmp", O_RDONLY);
    struct utmp utmp;
    int usr = 0;

    if (fd == -1) {
        printw("0 user, ");
        return;
    }
    while (read(fd, &utmp, sizeof(struct utmp)) == sizeof(struct utmp))
        if (utmp.ut_type == USER_PROCESS
            && strcmp(utmp.ut_line, "~") != 0
            && strcmp(utmp.ut_line, "seat0") != 0
            && strcmp(utmp.ut_user, "\0") != 0)
            usr++;
    close(fd);
    if (usr > 1)
        printw("%d users, ", usr);
    else
        printw("%d user, ", usr);
}

static void change_date(struct time_s *btime)
{
    if (btime->minutes >= 60) {
        btime->hours += btime->minutes / 60;
        btime->minutes = btime->minutes % 60;
    }
    if (btime->seconds >= 60) {
        btime->minutes += btime->seconds / 60;
        btime->seconds = btime->seconds % 60;
    }
}

static void put_date(struct time_s *time_s)
{
    int fd = open("/proc/stat", O_RDONLY);
    char buff[5000];
    int btime_sec = 0;
    struct time_s btime = {0, 0, 0, 0, 0.0};

    if (fd == -1)
        return;
    read(fd, buff, 5000);
    btime_sec = atoi(strstr(buff, "btime") + 6);
    btime = (struct time_s)
        {btime_sec % 86400 % 3600 % 60 + time_s->seconds,
        btime_sec % 86400 % 3600 / 60 + time_s->minutes,
        (btime_sec % 86400 / 3600 + time_s->hours) % 24 + 1, 0, 0.0};
    change_date(&btime);
    printw("%02d:%02d:%02d ", btime.hours, btime.minutes, btime.seconds);
    close(fd);
}

static void display_uptime_s(struct time_s *time_s)
{
    printw("up ");
    if (time_s->days > 1)
        printw("%d days, ", time_s->days);
    if (time_s->days == 1)
        printw("%d day, ", time_s->days);
    if (time_s->hours > 0)
        printw("%d:%d, ", time_s->hours, time_s->minutes);
    if (time_s->hours == 0)
        printw("%d min, ", time_s->minutes);
}

void put_uptime_s(void)
{
    FILE *file = fopen("/proc/uptime", "r");
    char *buff = NULL;
    size_t index_line = 0;
    int uptime_s = 0;
    struct time_s time_s;

    if (file == NULL)
        return;
    if (getline(&buff, &index_line, file) == -1)
        return;
    uptime_s = atoi(buff);
    free(buff);
    time_s = (struct time_s){uptime_s % 86400 % 3600 % 60,
    uptime_s % 86400 % 3600 / 60,
        uptime_s % 86400 / 3600, uptime_s / 86400, 0.0};
    put_date(&time_s);
    display_uptime_s(&time_s);
    fclose(file);
}

void putloadavg(void)
{
    int fd = open("/proc/loadavg", O_RDONLY);
    char buff[100];
    int nelem = 3;
    char *list[nelem];

    if (fd == -1)
        return;
    read(fd, buff, 100);
    list[0] = strtok(buff, " ");
    for (int i = 1; i < nelem; i++)
        list[i] = strtok(NULL, " ");
    printw("load average: %.2f, %.2f, %.2f\n",
        atof(list[0]), atof(list[1]), atof(list[2]));
    close(fd);
}

void first_line(int *lines, int height)
{
    (*lines)++;
    if (*lines >= height)
        return;
    printw("top - ");
    put_uptime_s();
    get_nbr_usr();
    putloadavg();
}
