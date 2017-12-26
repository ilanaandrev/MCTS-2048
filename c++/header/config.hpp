#pragma once

/******************************************
 * Project: MCT-TFE
 * File: config.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <map>

#include "types_macros.hpp"

// Grid is always square.
extern uint GRID_WIDTH;
extern uint GRID_SIZE;

// Win requirement
extern uint WIN_REQ;

// Heuristics
extern bool VAL_H;
extern long long int LEAF_WEIGHT;

// Directions
extern char DIR[4];
extern uint DIR_SIZE;
extern std::map<char, int> DIR_TO_NUM;