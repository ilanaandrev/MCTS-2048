/******************************************
 * Project: MCT-TFE
 * File: main.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <iostream>

#include "TFE.hpp"

int main() {
    TFE tfe;
    tfe.putNew();
    tfe.putNew();
    tfe.display();
    tfe.move('l');
    std::cout << "------------" << std::endl;
    tfe.display();
}