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