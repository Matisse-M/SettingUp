/*
** EPITECH PROJECT, 2023
** setting_up
** File description:
** Algorithm to find the biggest square
*/

#include "my.h"
#include "bsq.h"

static int stop_the_loop(bsq_t *bsq, int i, int j, int nb)
{
    for (int y = 0; y < nb; y++) {
        if (bsq->map[i][j] != '.')
            return (0);
        j++;
    }
    return (1);
}

static int is_square(bsq_t *bsq, int i, int j, int nb)
{
    for (int x = 0; x < nb; x++) {
        if (stop_the_loop(bsq, i, j, nb) == 0)
            return (0);
        i++;
    }
    return (1);
}

static int recursivity(bsq_t *bsq, int i, int j, int nb)
{
    if (j + nb < bsq->cols && i + nb < bsq->rows) {
        if (is_square(bsq, i, j, nb + 1) == 1)
            return (recursivity(bsq, i, j, nb + 1));
        return (nb);
    }
    return (nb);
}

static int free_place(bsq_t *bsq, int i, int j)
{
    if (bsq->map[i][j] == '.' && i < bsq->rows - bsq->biggest &&
        j < bsq->cols - bsq->biggest)
        return (recursivity(bsq, i, j, 1));
    return (0);
}

static void switch_to_x(bsq_t *bsq, int i, int j)
{
    if (bsq->biggest < free_place(bsq, i, j)) {
        bsq->biggest = free_place(bsq, i, j);
        bsq->x = i;
        bsq->y = j;
    }
}

static void find_biggest_square(bsq_t *bsq)
{
    int i = 0;
    int j = 0;

    while (i < bsq->rows) {
        while (j < bsq->cols) {
            switch_to_x(bsq, i, j);
            j++;
        }
        j = 0;
        i++;
    }
}

void setting_up(bsq_t *bsq)
{
    find_biggest_square(bsq);
    for (int i = 0; i < bsq->biggest; i++) {
        for (int j = 0; j < bsq->biggest; j++)
            bsq->map[bsq->x + i][bsq->y + j] = 'x';
    }
}
