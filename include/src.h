/*
** EPITECH PROJECT, 2024
** src.h
** File description:
** src.h
*/

#ifndef SRC_H_
    #define SRC_H_
    #include <curses.h>
    #include <fcntl.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <time.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <ctype.h>
    #include <sys/ioctl.h>
    #include <sys/stat.h>
    #include <pwd.h>
    #include <errno.h>
    #include <utmp.h>
    #define STATREAD 256
    #define STATUSREAD 2048
    #define MEMINFOREAD 2048
    #define MEBIBIT 1024.0

struct time_s {
    int seconds;
    int minutes;
    int hours;
    int days;
    float fseconds;
};

struct type {
    int total;
    int running;
    int sleeping;
    int stopped;
    int zombie;
};

struct linked_list_s {
    char *pid;
    char *user;
    char *priority;
    char *nice;
    char *virt;
    char *res;
    char *shr;
    char state;
    struct time_s time_s;
    char *name;
    struct linked_list_s *next_node;
};

void display(int offset);
void first_line(int *lines, int height);
void second_line(int *lines, int height);
void mem_swap_lines(int *lines, int height);
void display_tasks(int *lines, int height, int offset);
int free_list_stat(int nbvalues, char *list_stats[], int fd);
char *strcatpath(char *foldername, char *pid, char *filename);
int getinstatus(struct linked_list_s *head);
int getinstat(struct linked_list_s *head);

#endif
