/******************************************
 * Project: MCT-TFE
 * File: main.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TFE.hpp"
#include "MCT.hpp"

int main() {
    // Init seed with nanosecond time.
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    std::srand((time_t)ts.tv_nsec);

    TFE tfe;
    tfe.putNew();
    tfe.putNew();
    tfe.display();
    std::cout << "-----------" << std::endl;

    MCT mct(tfe);
    char act = mct.run(0, true);
    std::cout << "AI Choose: " << act << std::endl;
    if(act != 'E')
        tfe.move(act);
    tfe.display();
}