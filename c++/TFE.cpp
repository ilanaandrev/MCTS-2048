#include "TFE.hpp"

TFE::TFE() {
    grid = new uint[GRID_SIZE]();
}

TFE::~TFE() {
    delete[] grid;
}

void TFE::display() {
    print_grid(grid);
}

void TFE::move(char dir) {
    move_grid(grid, dir);
}

bool TFE::putNew() {
    auto cells = get_cells_where(grid, 0);
    if(cells.size() == 0)
        return false;

    int randNumber = rand() % (cells.size() - 1);
    uint loc = cells[randNumber];

    // Set the value
    randNumber = (rand() % 100) + 1;
    if(randNumber > 10)
        grid[loc] = 2;
    else
        grid[loc] = 4;
    
    return true;
}

std::vector<std::pair<char, uint *>> TFE::availDir() {
    std::vector<std::pair<char, uint *>> res;
    // If empty, we can take any direction
    if(max_grid(grid) == 0) {
        // Call memcpy only once.
        for(uint x = 0; x < DIR_SIZE; ++x) {
            uint *val = new uint[GRID_SIZE];
            std::memcpy(val, grid, GRID_SIZE);
            res.push_back(std::pair<char, uint *>(DIR[x], val));
        }
        return res;
    }

    // Try moving our values.
    for(uint x = 0; x < DIR_SIZE; ++x) {
        uint *val = new uint[GRID_SIZE];
        std::memcpy(val, grid, GRID_SIZE);
        move_grid(val, DIR[x]);

        // check if same
        if(is_equal(val, grid)){
            delete[] val;
            continue;
        }
        // Not the same, add it to result.
        res.push_back(std::pair<char, uint *>(DIR[x], val));
    }

    return res;
}

bool TFE::isWin() {
    return (max_grid(grid) == WIN_REQ);
}

bool TFE::isLose() {
    std::vector<std::pair<char, uint*>> resVect = availDir();
    // Check size
    bool res = (resVect.size() == 0);
    
    // Clean up
    for(uint x = 0; x < resVect.size(); ++x)
        delete[] resVect[x].second;

    return res;
}