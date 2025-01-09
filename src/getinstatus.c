/*
** EPITECH PROJECT, 2024
** B-PSU-100-PAR-1-1-mytop-ariel.amriou
** File description:
** getinstatus.c
*/

#include "src.h"

static void get_name(char *buff, struct linked_list_s *head)
{
    char *tmp = NULL;
    char *cpbuff = strdup(buff);

    tmp = strstr(cpbuff, "Name:");
    tmp = strtok(tmp, "\t");
    tmp = strtok(NULL, "\n");
    head->name = strdup(tmp);
    free(cpbuff);
}

static void get_state(char *buff, struct linked_list_s *head)
{
    char *tmp = NULL;
    char *cpbuff = strdup(buff);

    tmp = strstr(cpbuff, "State:");
    tmp = strtok(tmp, "\t");
    tmp = strtok(NULL, " ");
    head->state = *tmp;
    free(cpbuff);
}

static void get_virt(char *buff, struct linked_list_s *head)
{
    char *tmp = NULL;
    char *cpbuff = strdup(buff);

    tmp = strstr(cpbuff, "VmSize:");
    head->virt = strdup("0");
    if (tmp != NULL) {
        tmp = strtok(tmp, "\t");
        head->virt = strdup(strtok(NULL, " "));
    }
    free(cpbuff);
}

static void get_res(char *buff, struct linked_list_s *head)
{
    char *tmp = NULL;
    char *cpbuff = strdup(buff);

    tmp = strstr(cpbuff, "VmRSS:");
    head->res = strdup("0");
    if (tmp != NULL) {
        tmp = strtok(tmp, " ");
        head->res = strdup(strtok(NULL, " "));
    }
    free(cpbuff);
}

static void get_shr(char *buff, struct linked_list_s *head)
{
    char *tmp = NULL;
    char *cpbuff = strdup(buff);

    tmp = strstr(buff, "RssFile:");
    head->shr = strdup("0");
    if (tmp != NULL) {
        tmp = strtok(tmp, " ");
        head->shr = strdup(strtok(NULL, " "));
    }
    free(cpbuff);
}

int getinstatus(struct linked_list_s *head)
{
    char *path = strcatpath("/proc/", head->pid, "/status");
    int fd = open(path, O_RDONLY);
    char buff[STATUSREAD] = {0};

    free(path);
    if (fd == -1 || path == NULL || read(fd, buff, STATUSREAD) == -1)
        return 84;
    get_name(buff, head);
    get_state(buff, head);
    get_virt(buff, head);
    get_res(buff, head);
    get_shr(buff, head);
    close(fd);
    return 0;
}
