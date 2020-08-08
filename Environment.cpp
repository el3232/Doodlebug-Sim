//
// Created by Liza Leshchenko on 2019-07-05.
//

#include <iostream>

#include "Environment.h"
#include "Organism.h"
#include "Doodlebug.h"
#include "Ant.h"
#include "Constants.h"

Environment::Environment() = default;

Environment::~Environment() {
    for (int i = 0; i < ENVIRONMENT_HEIGHT; i++) {
        for (int j = 0; j < ENVIRONMENT_LENGTH; j++) {
            if(grid[i][j] != nullptr) {
                delete grid[i][j];
            }
        }
    }
}


void Environment::render() {
    // prints the environment
    // - for null
    // X for Doodlebug
    // o for Ant

    for (int i = 0; i < ENVIRONMENT_HEIGHT; i++) {
        for (int j = 0; j < ENVIRONMENT_LENGTH; j++) {
            if (grid[i][j] == nullptr) {
                std::cout << " - ";
            } else if (grid[i][j]->getType() == "Doodlebug") {
                std::cout << " X ";
            } else if (grid[i][j]->getType() == "Ant") {
                std::cout << " o ";
            } else if (grid[i][j]->getType() == "Org") {
                std::cout << " " << grid[i][j]->getStepCount() << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Environment::generateDoodlebugs() {
    int doodlebugCount = 0;
    while (doodlebugCount < NUM_OF_DOODLEBUGS) {
        Doodlebug *dood = new Doodlebug("Doodlebug", this);
        int row = dood->getRow();
        int col = dood->getCol();
        if (grid[row][col] == nullptr) {
            grid[row][col] = dood;
            doodlebugCount++;
        }
    }
}

void Environment::generateAnts() {
    int antCount = 0;
    while (antCount < NUM_OF_ANTS) {
        Ant *ant = new Ant("Ant", this);
        int row = ant->getRow();
        int col = ant->getCol();
        if (grid[row][col] == nullptr) {
            grid[row][col] = ant;
            antCount++;
        }
    }
}


bool Environment::checkGrid(int direction, int row, int col) {
    bool isLegalMove;


    switch (direction) {
        case DOWN:
            isLegalMove = (((row + 1) <= (ENVIRONMENT_HEIGHT - 1)) && (grid[row + 1][col] == nullptr));
            break;

        case UP:
            isLegalMove = (((row - 1) >= 0) && (grid[row - 1][col] == nullptr));
            break;

        case RIGHT:
            isLegalMove = (((col + 1) <= (ENVIRONMENT_LENGTH - 1)) && (grid[row][col + 1] == nullptr));
            break;

        case LEFT:
            isLegalMove = (((col - 1) >= 0) && (grid[row][col - 1] == nullptr));
            break;

        default:
            std::cout << "Not a legal direction" << std::endl;
            break;
    }

    return isLegalMove;
}

bool Environment::checkForAnts(int direction, int row, int col) {
    bool canEatAnt = false;


    switch (direction) {
        case DOWN:
            if (grid[row + 1][col] != nullptr) {
                canEatAnt = (((row + 1) <= (ENVIRONMENT_HEIGHT - 1)) && (grid[row + 1][col]->getType() == "Ant"));
            }
            break;

        case UP:
            if (grid[row - 1][col] != nullptr) {
                canEatAnt = (((row - 1) >= 0) && (grid[row - 1][col]->getType() == "Ant"));
            }
            break;

        case RIGHT:
            if (grid[row][col + 1] != nullptr) {
                canEatAnt = (((col + 1) <= (ENVIRONMENT_LENGTH - 1)) && (grid[row][col + 1]->getType() == "Ant"));
            }
            break;

        case LEFT:
            if (grid[row][col - 1] != nullptr) {
                canEatAnt = (((col - 1) >= 0) && (grid[row][col - 1]->getType() == "Ant"));
            }
            break;

        default:
            std::cout << "Not a legal direction" << std::endl;
            break;
    }

    return canEatAnt;
}

void Environment::moveDoodles() {

    // put starve here?


    for (int i = 0; i < ENVIRONMENT_HEIGHT; i++) {
        for (int j = 0; j < ENVIRONMENT_LENGTH; j++) {
            if (grid[i][j] != nullptr && grid[i][j]->getType() == "Doodlebug") {
                auto *doodle = dynamic_cast<Doodlebug *>(grid[i][j]);
                if (!doodle->getHasMoved()) {
                    doodle->move();
                }
            }
        }
    }

    for (int i = 0; i < ENVIRONMENT_HEIGHT; i++) {
        for (int j = 0; j < ENVIRONMENT_LENGTH; j++) {
            if (grid[i][j] != nullptr && grid[i][j]->getType() == "Doodlebug") {
                grid[i][j]->setHasMoved(false);
            }
        }
    }

}

void Environment::moveAnts() {

    for (int i = 0; i < ENVIRONMENT_HEIGHT; i++) {
        for (int j = 0; j < ENVIRONMENT_LENGTH; j++) {
            if (grid[i][j] != nullptr && grid[i][j]->getType() == "Ant") {
                auto *ant = dynamic_cast<Ant *>(grid[i][j]);
                if (!ant->getHasMoved()) {
                    ant->move();
                }
            }
        }
    }

    for (int i = 0; i < ENVIRONMENT_HEIGHT; i++) {
        for (int j = 0; j < ENVIRONMENT_LENGTH; j++) {
            if (grid[i][j] != nullptr && grid[i][j]->getType() == "Ant") {
                grid[i][j]->setHasMoved(false);
            }
        }
    }

}

void Environment::setOldGridNull(int row, int col) {
    grid[row][col] = nullptr;
}


void Environment::renderMovement(int newRow, int newCol, Organism *critPtr) {

    int oldRow = critPtr->getRow();
    int oldCol = critPtr->getCol();
    addToGridAt(newRow, newCol, critPtr);
    setOldGridNull(oldRow, oldCol);
}


void Environment::addToGridAt(int newRow, int newCol, Organism *critPtr) {
    grid[newRow][newCol] = critPtr;
    critPtr->setRow(newRow);
    critPtr->setCol(newCol);
}




