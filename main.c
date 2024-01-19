/*
** EPITECH PROJECT, 2023
** main
** File description:
** main()
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "my.h"
#include "bsq.h"

static int is_pattern_okay(char *nb, char *pattern)
{
    for (int i = 0; nb[i] != '\0'; i++) {
        if (nb[i] < '0' || nb[i] > '9')
            return (0);
    }
    if (pattern[0] == '\0')
        return (0);
    for (int i = 0; pattern[i] != '\0'; i++) {
        if (pattern[i] != '.' && pattern[i] != 'o')
            return (0);
    }
    return (1);
}

static int is_buffer_okay(char *buffer)
{
    int x = -1;
    int j = 0;
    int n = 0;

    for (int i = my_intlen(my_getnbr(buffer)) + 1; buffer[i] != '\0'; i++) {
        if (buffer[i] != '.' && buffer[i] != 'o' && buffer[i] != '\n')
            return (0);
        if (buffer[i] == '\n' && x == -1)
            x = j;
        if (buffer[i] == '\n' && x != j)
            return (0);
        if (buffer[i] == '\n' && x == j)
            j = -1;
        if (buffer[i] == '\n')
            n++;
        j++;
    }
    if (n != my_getnbr(buffer))
        return (0);
    return (1);
}

static int check_valid_file(char *buffer)
{
    if (my_strlen(buffer) == 0)
        return (0);
    if (my_getnbr(buffer) == 0)
        return (0);
    if (my_strlen(buffer) == my_intlen(my_getnbr(buffer)) + 1)
        return (0);
    if (is_buffer_okay(buffer) == 0)
        return (0);
    return (1);
}

static int restart_x(char *str, int x)
{
    if (x >= my_strlen(str))
        x = 0;
    return (x);
}

static void fill_map(bsq_t *bsq, char *buffer)
{
    int i = my_intlen(bsq->rows) + 1;
    int k = my_intlen(bsq->rows) + 1;

    for (int j = 0; j < bsq->rows && buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n') {
            bsq->map[j] = my_strndup(&buffer[k], i - k);
            i++;
            k = i;
            j++;
        }
    }
    bsq->map[my_getnbr(buffer)] = NULL;
}

static bsq_t open_map(char **av)
{
    bsq_t bsq = {NULL, 0, 0, 0, 0, 0};
    struct stat s;
    int fd = open(av[1], O_RDONLY);
    char *buffer = NULL;

    if (fd == -1)
        return (bsq);
    if (stat(av[1], &s) == -1)
        return (bsq);
    buffer = malloc(sizeof(char) * (s.st_size + 1));
    read(fd, buffer, s.st_size);
    buffer[s.st_size] = '\0';
    if (check_valid_file(buffer) == 0)
        return ((bsq_t) {NULL, 0, 0, 0, 0, 0});
    bsq.rows = my_getnbr(buffer);
    bsq.map = malloc(sizeof(char *) * (my_getnbr(buffer) + 1));
    fill_map(&bsq, buffer);
    bsq.cols = my_strlen(bsq.map[0]);
    free(buffer);
    return (bsq);
}

static bsq_t generate_map(char **av)
{
    bsq_t bsq = {NULL, 0, 0, 0, 0, 0};
    int x = 0;

    bsq.cols = my_getnbr(av[1]);
    bsq.rows = my_getnbr(av[1]);
    bsq.map = malloc(sizeof(char *) * (bsq.rows + 1));
    for (int i = 0; i < bsq.rows; i++) {
        bsq.map[i] = malloc(sizeof(char) * (bsq.cols + 1));
        for (int j = 0; j < bsq.rows; j++) {
            x = restart_x(av[2], x);
            bsq.map[i][j] = av[2][x];
            x++;
        }
        bsq.map[i][bsq.cols] = '\0';
    }
    bsq.map[bsq.rows] = NULL;
    return (bsq);
}

int main(int ac, char **av)
{
    bsq_t bsq;

    if (ac < 2 || ac > 3)
        return (84);
    if (ac == 2) {
        bsq = open_map(av);
        if (bsq.map == NULL)
            return (84);
    }
    if (ac == 3) {
        if (is_pattern_okay(av[1], av[2]) == 0)
            return (84);
        bsq = generate_map(av);
    }
    setting_up(&bsq);
    my_show_word_array(bsq.map);
    for (int i = 0; bsq.map[i] != NULL; i++)
        free(bsq.map[i]);
    free(bsq.map);
    return (0);
}
