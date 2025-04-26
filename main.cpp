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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
//#include <filesystem>

#include "TFE.hpp"
#include "MCT.hpp"
#include "grid_util.hpp"

int main() {
    // Init seed with nanosecond time.
    std::srand(time(NULL));

     std::string output_folder = "my-naive-output";
     //std::filesystem::create_directory(output_folder); // will not overwrite if exists

    int NUM_GAMES = 100;
    for (int game_num = 0; game_num < NUM_GAMES; ++game_num) {
        TFE tfe;
        tfe.putNew();
        tfe.putNew();

        auto start_time = std::chrono::steady_clock::now();


        std::cout << "STARTING BOARD: " << std::endl;
        tfe.display();
        std::cout << std::endl;
        
        while(!tfe.isWin() && !tfe.isLose()) {
            MCT mct(tfe);
            char act = mct.run(MONTE_CARLO, true);
            tfe.move(act);
            tfe.putNew();
        }

        auto end_time = std::chrono::steady_clock::now();
        double elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() / 1000000.0;

        // Save game result
        std::ofstream out(output_folder + "/game_" + std::to_string(game_num) + ".txt");

        if (out.is_open()) {
            out << "Game #" << game_num << "\n";
            out << "Final Board:\n";
            printGraph(tfe.getGrid(), out); 
            out << "\n";
            out << "Is Win?: " << tfe.isWin() << "\n";
            out << "Is Lose?: " << tfe.isLose() << "\n";
            out << "Time (seconds): " << elapsed_seconds << "\n";
            out.close();
        }
    }

    std::cout << "Finished running " << NUM_GAMES << " games.\n";
}