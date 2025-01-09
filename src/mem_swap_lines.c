/*
** EPITECH PROJECT, 2024
** B-PSU-100-PAR-1-1-mytop-ariel.amriou
** File description:
** mem_swap_lines.c
*/

#include "src.h"

static float get_mem_swap(char const *delim, char *buff)
{
    char *tmp = strstr(buff, delim);

    strtok(tmp, " ");
    tmp = strtok(NULL, " ");
    return atoi(tmp) / MEBIBIT;
}

static void mem_line(char *buff)
{
    char *cpbuff = strdup(buff);
    float total_mem = get_mem_swap("MemTotal:", cpbuff);
    float free_mem = get_mem_swap("MemFree:", cpbuff);
    float available_mem = total_mem - get_mem_swap("MemAvailable:", cpbuff);
    float buffers = get_mem_swap("Buffers:", cpbuff);
    float cached = get_mem_swap("Cached:", cpbuff);
    float sreclaimable = 0.0;
    float buffers_cache = 0.0;

    free(cpbuff);
    cpbuff = strdup(buff);
    sreclaimable = get_mem_swap("SReclaimable:", cpbuff);
    buffers_cache = buffers + cached + sreclaimable;
    printw("MiB Mem : %.1f total, %.1f free, %.1f used, %.1f buff/cache\n",
        total_mem, free_mem, available_mem, buffers_cache);
    free(cpbuff);
}

static void swap_line(char *buff)
{
    char *cpbuff = strdup(buff);
    float total_swap = get_mem_swap("SwapTotal:", cpbuff);
    float free_swap = get_mem_swap("SwapFree:", cpbuff);
    float used_swap = total_swap - free_swap;
    float available_mem = 0.0;

    free(cpbuff);
    cpbuff = strdup(buff);
    available_mem = get_mem_swap("MemAvailable:", cpbuff);
    printw("MiB Swap: %.1f total, %.1f free, %.1f used, %.1f avail Mem\n\n",
        total_swap, free_swap, used_swap, available_mem);
    free(cpbuff);
}

void mem_swap_lines(int *lines, int height)
{
    int fd = open("/proc/meminfo", O_RDONLY);
    char *buff = malloc(MEMINFOREAD);
    int i = 0;

    if (fd == -1 || buff == NULL)
        return;
    i = read(fd, buff, MEMINFOREAD);
    if (i == -1)
        return;
    buff[i] = '\0';
    *lines += 2;
    if (*lines < height)
        mem_line(buff);
    (*lines)++;
    if (*lines < height)
        swap_line(buff);
    free(buff);
}
