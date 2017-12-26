#include "MCTNode.hpp"

/******************************************
 * Project: MCT-TFE
 * File: MCTNode.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

MCTNode::MCTNode(MCTNode *parent, uint option, uint *grid) {
    this->parent = parent;
    this->option = option;
    this->grid = grid;

    // Create children options, must call after grid is set
    genOpt();

    // Check to see if we should adjust value.
    if(VAL_H) {
        if(children_options.size() != 0)
            val = valueFromGrid(grid);
        else if(max_grid(grid) == WIN_REQ)
            val = LEAF_WEIGHT;
        else
            val = -LEAF_WEIGHT;
    }
}

MCTNode::~MCTNode() {
    delete grid;
}

MCTNode* MCTNode::createChild() {
    if(children_options.size() == 0)
        return nullptr;
    
    // Find a random child.
    int randNumber = rand() % (children_options.size() - 1);
    uint opt = children_options[randNumber];

    // Delete option
    children_options.erase(children_options.begin() + (randNumber - 1));
    uint *optGrid = optToGrid(opt);
    MCTNode* resNode = new MCTNode(this, opt, optGrid);

    children.push_back(resNode);
    return resNode;
}

uint * MCTNode::optToGrid(uint opt) {
    uint v = (uint) (opt / (DIR_SIZE * GRID_SIZE));
    opt -= v * DIR_SIZE * GRID_SIZE;
    uint loc = (uint) (opt / DIR_SIZE);
    char d = DIR[opt % 4];

    uint *res = copy_grid(grid);
    move_grid(res, d);
    if(val == 0)
        AC(grid, (uint) (loc % 4), (uint) (loc / 4)) = 2;
    else
        AC(grid, (uint) (loc % 4), (uint) (loc / 4)) = 4;
    
    return res;
}

void MCTNode::genOpt() {
    std::vector<uint> res;
    // Generate all available options.
    // Assumes grid is available.
    auto avail = avail_dir(grid);

    for(uint x = 0; x < avail.size(); ++x) {
        std::vector<uint> where = get_cells_where(grid, 0);
        for(uint i = 0; i < where.size(); ++i) {
            res.push_back(DIR_TO_NUM[avail[x].first] + DIR_SIZE * (where[i]));
            res.push_back(DIR_TO_NUM[avail[x].first] + DIR_SIZE * (where[i] + GRID_SIZE));
        }
    }
    
    // Delete the generated avail
    for(auto i : avail)
        delete[] i.second;

    children_options = res;
}


long long int MCTNode::valueFromGrid(uint *A) {
    long long int res = 0;
    uint *fil = copy_grid(A);

    // Size after difference
    uint size = (GRID_WIDTH - 1) * GRID_WIDTH;
    uint *d = diff_grid(fil);
    clip(d, 0, 1, size);
    res += sum(d, size);
    delete[] d;
    
    // Rotate and do again.
    rotate_grid_90(fil);
    d = diff_grid(fil);
    clip(d, 0, 1, size);
    res += sum(d, size);
    delete[] d;

    delete[] fil;
    return res;
}