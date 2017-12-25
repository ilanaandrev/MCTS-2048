#include "grid_util.hpp"


/**
 * Basic single element multiplication.
 * Dimensions assumed GRID_WIDTH in config.
 */
void mult_grid(uint *A, uint *B) {
    for(unsigned int x = 0; x < GRID_SIZE; ++x)
        A[x] = A[x] * B[x];
}

/**
 * Get the cells with value equal to given val.
 * Returns a vector of cell locations, linearly.
 */
std::vector<uint> get_cells_where(uint *A, uint val) {
    std::vector<uint> res;
    for(uint x = 0; x < GRID_SIZE; ++x)
        if(A[x] == val)
            res.push_back(x);
    
    return res;
}

void move_cell(uint *A, int x, int y, char dir) {
    // Check zero
    if(AC(A, x, y) == 0)
        return;

    // Check boundary cases
    if(x <= 0 && dir == 'l')
        return;
    else if(x >= 3 && dir == 'r')
        return;
    else if(y <= 0 && dir == 'u')
        return;
    else if(y >= 3 && dir == 'd')
        return;

    int xval, yval;

    // Direction checking.
    if(dir == 'l'){ xval = -1; yval = 0; }
    else if(dir == 'r'){ xval = 1; yval = 0; }
    else if(dir == 'd'){ xval = 0; yval = 1; }
    else{ xval = 0; yval = -1; }

    int dx = x + xval;
    int dy = y + yval;
    for(;;) {
        // Edit condition switch.
        if(dir == 'l') { if(x >= 0) break ;}
        else if(dir == 'r') { if(x < 4) break ;}
        else if(dir == 'd') { if(y < 4) break ;}
        else { if(y >= 0) break ;}

       if(AC(A, dx, dy) == 0) {
           dx += xval; dy += yval;
       }
       else if(AC(A, dx, dy) == AC(A, x, y)) {
            AC(A, dx, dy) *= 2;
            AC(A, x, y) = 0;
            return;
       }
       else {
           break;
       }
    }

    AC(A, dx-xval, dy-yval) = AC(A, x, y);
    if((dy - yval != y) || (dx - xval != x))
        AC(A, x, y) = 0;
}

// Ugly, yes. Could I use lambdas? Probably
// But it works for now...
void move_grid(uint *A, char dir) {
    if(dir == 'l') {
        int dy = 0;
        while(dy < 4) {
            int dx = 0;
            while(dx < 4) {
                move_cell(A, dx, dy, dir);
                ++dx;
            }
            ++dy;
        }
    }
    else if(dir == 'r') {
        int dy = 3;
        while(dy >= 0) {
            int dx = 3;
            while(dx >= 0) {
                move_cell(A, dx, dy, dir);
                --dx;
            }
            --dy;
        }
    }
    else if(dir == 'd') {
        int dx = 3;
        while(dx >= 0) {
            int dy = 3;
            while(dy >= 0) {
                move_cell(A, dx, dy, dir);
                --dy;
            }
            --dx;
        }
    }
    else {
        int dx = 0;
        while(dx < 4) {
            int dy = 0;
            while(dy < 4) {
                move_cell(A, dx, dy, dir);
                ++dy;
            }
            ++dx;
        }
    }
}

// Check if grids are equal
bool is_equal(uint *A, uint *B) {
    for(uint x = 0; x < GRID_SIZE; ++x)
        if(A[x] != B[x])
            return false;
    return true;
}

/**
 * Find max element in the grid.
 */
uint max_grid(uint *grid) {
    uint max = 0;
    for(uint x = 0; x < GRID_SIZE; ++x)
        if(grid[x] > max)
            max = grid[x];
    return max;
}

/**
 * Print the grid
 */
void print_grid(uint *A) {
    for(uint x = 0; x < GRID_SIZE; ++x) {
        std::cout << A[x] << " ";
        if((x+1) % GRID_WIDTH == 0)
            std::cout << std::endl;
    }
}