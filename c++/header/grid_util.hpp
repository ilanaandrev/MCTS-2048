#pragma once

/******************************************
 * Project: MCT-TFE
 * File: matrix_util.h
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
 * Desc.: File to contain helpers for 
 *       grid manipulation.
*******************************************/

#include <vector>
#include <iostream>
#include <cstring>
#include <utility>

#include "config.hpp"
#include "types_macros.hpp"

uint * copy_grid(uint *A);
void mult_grid(uint *A, uint *B);
std::vector<uint> get_cells_where(uint *A, uint val);
void move_cell(uint *A, int x, int y, char dir);
void move_grid(uint *A, char dir);
bool is_equal(uint *A, uint *B);
uint max_grid(uint *grid);
void print_grid(uint *A);
std::vector<std::pair<char, uint *>> avail_dir(uint *grid);
void rotate_grid_90(uint *A);
uint *diff_grid(uint *A);

/* Matrix Specific Functions */
// These functions require specific size of grid since not assumed.

// Returns a new array of dim(GRID_WIDTH - 1, GRID_WIDTH)
// Clip the grid.
void clip(uint *A, uint min, uint max, uint size);
// Returns a summed number
long long int sum(uint *A, uint size);