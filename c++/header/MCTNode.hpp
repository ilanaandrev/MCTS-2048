/******************************************
 * Project: MCT-TFE
 * File: MCTNode.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <vector>
#include <random>

#include "types_macros.hpp"

class MCTNode {
    uint option;
    MCTNode *parent;
    uint total_games;
    uint total_wins;
    float UCB;
    long long int val;
    uint *grid;

    std::vector<uint> children;
    std::vector<uint> children_options;

    public:
        // NOTE: Grid is not copied.
        MCTNode(MCTNode *parent, uint option, uint *grid);
        
        // Grid guranteed to be deleted.
        ~MCTNode();

        /**
         * Create a child node.
         */
        MCTNode* createChild();

    private:
        /**
         * Encode future grid orientations by unique id.
         */
        void genOpt();

        /**
         * Decode unique option id to a grid orientation.
         */
        uint * optToGrid(uint opt);

        /**
         * Generates heuristic values from grid orientation.
         */
        long long int valueFromGrid(uint *A);
};