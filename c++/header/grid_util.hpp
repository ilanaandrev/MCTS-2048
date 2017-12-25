#pragma once

/******************************************
 * Project: MCT-TFE
 * File: matrix_util.h
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
 * Desc.: File to contain helpers for 
 *       grid manipulation.
*******************************************/

#include "config.hpp"
#include "types.hpp"

/**
 * Basic single element multiplication.
 * Dimensions assumed GRID_WIDTH in config.
 */
void mult_grid(uint *A, uint *B) {
    for(unsigned int x = 0; x < GRID_WIDTH; ++x)
        A[x] = A[x] * B[x];
}

/**
 * Find max element in the grid.
 */
uint max_grid(uint *grid) {
    uint max = 0;
    for(uint x = 0; x < GRID_WIDTH; ++x)
        if(grid[x] > max)
            max = grid[x];
    return max;
}