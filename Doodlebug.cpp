//
// Created by Liza Leshchenko on 2019-07-05.
//

#include "Doodlebug.h"
#include "Environment.h"
#include <random>
#include <iostream>
#include "Constants.h"
#include <vector>


Doodlebug::Doodlebug(std::string type, Environment *envPtrArg) : Organism("Doodlebug", envPtrArg, false) {

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(0, 19);

    int row = distr(generator);
    int col = distr(generator);
    setRow(row);
    setCol(col);
    starveCount = 0;
}


void Doodlebug::incStarveCount() {
    starveCount += 1;
}

void Doodlebug::resetStarveCount() {
    starveCount = 0;
}

bool Doodlebug::breedCycle() {
    return (getStepCount() > 0 && getStepCount() % DOODLEBUG_BREED == 0);
}


bool Doodlebug::eat() {
    std::vector<int> cells{DOWN, UP, RIGHT, LEFT};

    while (!cells.empty()) {
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_int_distribution<int> distr(0, cells.size() - 1);

        int index = distr(generator);
        int eatDirection = cells[index];
        cells.erase(cells.begin() + index);

        int oldRow = getRow();
        int oldCol = getCol();

        int newRow = oldRow;
        int newCol = oldCol;

        bool canEat = (envPtr->checkForAnts(eatDirection, oldRow, oldCol));

        if (canEat) {

            setHasMoved(true);
            resetStarveCount();

            getNewCellCoordinate(eatDirection, newRow, newCol);

            envPtr->renderMovement(newRow, newCol, this); // function to set grid to grid[newRow][newCol], deletes old grid coordinates
            return true;
        }
    }
    return false;
}

void Doodlebug::tryToMove() {

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(0, 3);

    int direction = distr(generator);

    int oldRow = getRow();
    int oldCol = getCol();

    int newRow = oldRow;
    int newCol = oldCol;

    bool canMove = (envPtr->checkGrid(direction, oldRow, oldCol));

    if (canMove) {

        setHasMoved(true);

        getNewCellCoordinate(direction, newRow, newCol);

        envPtr->renderMovement(newRow, newCol, this); // sets grid to grid[newRow][newCol], deletes old grid coordinates

    }

    incStarveCount();
}

void Doodlebug::move() {

    std::random_device rand_dev;

    incStepCount(); // increment step count

    if (eat()) {
        // try to eat
    }
    else {
        tryToMove();
        if (starveCount == STARVED) {
            envPtr->setOldGridNull(getRow(), getCol());
            delete this;
            return;
        }
    }

    if (breedCycle()) {
        breed();
    }
}

void Doodlebug::breed() {

    std::random_device rand_dev;

    std::vector<int> cells{DOWN, UP, RIGHT, LEFT};

    while (!cells.empty()) {
        std::mt19937 generator(rand_dev());
        std::uniform_int_distribution<int> distr(0, cells.size() - 1);

        int index = distr(generator);
        int direction = cells[index];
        cells.erase(cells.begin() + index);


        bool canBreed = (envPtr->checkGrid(direction, getRow(), getCol()));

        if (canBreed) {
            // checks if the grid cell in the chosen direction is empty for spawning into

            int newRow = getRow();
            int newCol = getCol();

            getNewCellCoordinate(direction, newRow, newCol);


            Organism *child = new Doodlebug("Doodlebug", envPtr);
            child->setHasMoved(true);
            envPtr->addToGridAt(newRow, newCol, child);

            return;
        }
    }
}


