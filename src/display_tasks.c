/*
** EPITECH PROJECT, 2024
** B-PSU-100-PAR-1-1-mytop-ariel.amriou
** File description:
** display_tasks.c
*/

#include "src.h"

void destroy_linked_list_s(struct linked_list_s *head)
{
    struct linked_list_s tmp = *head;

    while (head != NULL) {
        tmp = *head;
        free(head);
        head = tmp.next_node;
    }
}

void putnode(struct linked_list_s **previus, char *str)
{
    struct linked_list_s *node = 0;

    node = malloc(sizeof(struct linked_list_s));
    node->pid = strdup(str);
    node->next_node = *previus;
    *previus = node;
}

static struct linked_list_s *create_chain(void)
{
    DIR *dir = opendir("/proc");
    struct dirent *info = NULL;
    struct linked_list_s *node = 0;

    if (dir == NULL) {
        perror("");
        return NULL;
    }
    info = readdir(dir);
    while (info != NULL) {
        if (isdigit(*info->d_name))
            putnode(&node, info->d_name);
        info = readdir(dir);
    }
    closedir(dir);
    return node;
}

static void get_user(struct linked_list_s *head)
{
    struct stat pidstat;
    struct passwd *pw = NULL;
    char *path = strcatpath("/proc/", head->pid, "");

    stat(path, &pidstat);
    free(path);
    pw = getpwuid(pidstat.st_uid);
    if (strlen(pw->pw_name) > 8) {
        pw->pw_name[7] = '+';
        pw->pw_name[8] = '\0';
    }
    head->user = strdup(pw->pw_name);
}

static int populate_linked_list_s(struct linked_list_s *head)
{
    get_user(head);
    if (getinstat(head) == 84) {
        free(head->pid);
        return 84;
    }
    if (getinstatus(head) == 84) {
        free(head->pid);
        free(head->user);
        free(head->nice);
        free(head->priority);
        return 84;
    }
    return 0;
}

static void free_content(struct linked_list_s *head)
{
    free(head->user);
    free(head->priority);
    free(head->virt);
    free(head->res);
    free(head->shr);
    free(head->pid);
}

static void display_linked_list_s(struct linked_list_s *head,
    int *lines, int height, int offset)
{
    struct linked_list_s *next = NULL;

    for (int i = 0; head->next_node != NULL && i < offset; i++)
        head = head->next_node;
    while (head != NULL && *lines < height) {
        if (populate_linked_list_s(head) == 0) {
            (*lines)++;
            printw("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%c\t%d:%.2f\t%s\n",
                head->pid, head->user, head->priority, head->nice,
                head->virt, head->res, head->shr, head->state,
                head->time_s.minutes, head->time_s.fseconds, head->name);
            free_content(head);
        }
        next = head->next_node;
        head = next;
    }
}

void display_tasks(int *lines, int height, int offset)
{
    struct linked_list_s *node = create_chain();

    if (node == NULL)
        return;
    (*lines)++;
    if (*lines >= height)
        return;
    attron(COLOR_PAIR(2));
    printw("PID\tUSER\tPR\tNI\tVIRT\tRES\tSHR\tS\tTIME+\tCOMMAND\n");
    attron(COLOR_PAIR(1));
    display_linked_list_s(node, lines, height, offset);
    destroy_linked_list_s(node);
}
