/******************************************
 * Project: MCT-TFE
 * File: main.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
 * Edited By: Ilana Andrev
*******************************************/

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

#include "TFE.hpp"
#include "MCT.hpp"
#include "grid_util.hpp"

int getHighestTile(const uint* grid) {
    int highest = 0;
    for (int i = 0; i < GRID_SIZE; ++i) {
        if (grid[i] > highest)
            highest = grid[i];
    }
    return highest;
}

int main() {
    std::srand(time(NULL)); // Seed RNG

    std::string output_file = "hour_run_output.txt";
    std::ofstream out(output_file);
    if (!out.is_open()) {
        std::cerr << "Error: Could not open output file.\n";
        return 1;
    }

    auto run_start = std::chrono::steady_clock::now();
    int game_num = 0;
    int total_highest_tile = 0;
    int max_highest_tile = 0;
    double total_game_time = 0.0;

    while (true) {
        auto current_time = std::chrono::steady_clock::now();
        double total_elapsed = std::chrono::duration_cast<std::chrono::seconds>(current_time - run_start).count();

        if (total_elapsed >= 3600) break;

        TFE tfe;
        tfe.putNew();
        tfe.putNew();

        auto start_time = std::chrono::steady_clock::now();

        out << "Game #" << game_num << "\n";
        out << "\n";

        while (!tfe.isWin() && !tfe.isLose()) {
            MCT mct(tfe);
            char act = mct.run(MONTE_CARLO, true);
            tfe.move(act);
            tfe.putNew();
        }

        auto end_time = std::chrono::steady_clock::now();
        double game_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() / 1e6;
        total_game_time += game_time;

        int highest_tile = getHighestTile(tfe.getGrid());
        total_highest_tile += highest_tile;
        if (highest_tile > max_highest_tile)
            max_highest_tile = highest_tile;

        out << "Final Board:\n";
        printGraph(tfe.getGrid(), out);
        out << "Game Time (seconds): " << game_time << "\n";
        out << "Highest Tile: " << highest_tile << "\n\n";

        game_num++;
    }

    double avg_highest_tile = static_cast<double>(total_highest_tile) / game_num;
    double avg_game_time = total_game_time / game_num;

    out << "=============================\n";
    out << "Run Summary:\n";
    out << "Total Games Played: " << game_num << "\n";
    out << "Average Highest Tile: " << avg_highest_tile << "\n";
    out << "Max Highest Tile: " << max_highest_tile << "\n";
    out << "Average Game Time (seconds): " << avg_game_time << "\n";
    out.close();

    std::cout << "Finished 1-hour run. " << game_num << " games played.\n";
    std::cout << "Output saved to " << output_file << "\n";

    return 0;
}
