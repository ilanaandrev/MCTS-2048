#pragma once

/******************************************
 * Project: MCT-TFE
 * File: TFE.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <vector>

#include "config.hpp"
#include "grid_util.hpp"
#include "types.hpp"

class TFE {
    // Save grid as 1d array.
    uint *grid;

    public:
        TFE();
        ~TFE();

        

        // Move All Directions and Return Results.
        std::vector<uint *> availDir();

        // Check if win. Linear to grid size.
        bool isWin();
};