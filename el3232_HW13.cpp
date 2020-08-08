#include <iostream>
#include <string>
#include "Environment.h"
#include "Doodlebug.h"
#include "Organism.h"

class Doodlebug;

using namespace std;

int main() {

    Environment* env = new Environment();
    env->generateDoodlebugs();
    env->generateAnts();
    env->render();

    if (std::cin.get() == '\n')
        ;

    bool keepRunning = true;
    while (keepRunning) {

        env->moveDoodles();
        env->moveAnts();
        env->render();

        if (std::cin.get() == '\n') {
            // do nothing
        } else {
            keepRunning = false ;
        }
    }

    return 0;
}