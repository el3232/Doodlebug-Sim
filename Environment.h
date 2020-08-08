//
// Created by Liza Leshchenko on 2019-07-05.
//

#ifndef EL3232_HW13_DOODLEBUG_ENVIRONMENT_H
#define EL3232_HW13_DOODLEBUG_ENVIRONMENT_H

#include "Constants.h"
class Organism;

class Environment {
private:
    Organism * grid[ENVIRONMENT_HEIGHT][ENVIRONMENT_LENGTH] = {};
public:
    Environment();
    ~Environment();

    void render();
    // Prints the Environment

    void generateDoodlebugs();
    // Populates an Environment with Doodles (5 now)

    void generateAnts();
    // Populates an Environment with Ants (100 now)

    bool checkGrid(int cellDirection, int row, int col);
    // Checks if grid location at chosen random direction is empty for moving to

    bool checkForAnts(int cellDirection, int row, int col);
    // Checks if grid location at chosen random direction has an Ant for eating

    void setOldGridNull(int row, int col);
    // Sets previous grid location to nullPtr after moving from it or dying (actually maybe just dying)

    void moveDoodles();
    // Initializes the whole Doodle movement

    void moveAnts();
    // Initializes the whole Ant movement

    void renderMovement(int newRow, int newCol, Organism* critPtr);
    // Used for moving to a specific grid location and setting previous location to nullPtr
    // This includes Doodlebugs eating Ants

    void addToGridAt(int row, int col, Organism* critPtr);
    // Used for breeding - finds a viable cell for the baby to spawn
};


#endif //EL3232_HW13_DOODLEBUG_ENVIRONMENT_H
