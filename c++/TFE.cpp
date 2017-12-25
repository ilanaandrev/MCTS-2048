#include "TFE.hpp"

TFE::TFE() {
    grid = new int[GRID_WIDTH];
}

TFE::~TFE() {
    delete[] grid;
}



TFE::isWin() {
    return (max_grid(grid) == WIN_REQ);
}