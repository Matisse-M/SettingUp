/*
** EPITECH PROJECT, 2023
** main
** File description:
** main()
*/

#pragma once

typedef struct bsq_s {
    char **map;
    int rows;
    int cols;
    int biggest;
    int x;
    int y;
} bsq_t;

void setting_up(bsq_t *bsq);
