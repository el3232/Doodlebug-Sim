//
// Created by Liza Leshchenko on 2019-07-05.
//

#include "Ant.h"
#include "Environment.h"
#include <random>
#include <iostream>
#include "Constants.h"
#include <vector>

Ant::Ant(const std::string &type, Environment *envPtrArg) : Organism("Ant", envPtrArg, false) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(0, 19);

    int row = distr(generator);
    int col = distr(generator);
    setRow(row);
    setCol(col);
}


//void Ant::getEaten() {
//    if (gotEaten) {
//        envPtr->setOldGridNull(getRow(), getCol());
//        delete this;
//        //destroy ants location in grid and then its own envPtr
//    }
//}

bool Ant::breedCycle() {
    return (getStepCount() > 0 && getStepCount() % ANT_BREED == 0);
}

void Ant::move() {

    incStepCount();

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(0, 3);

    int direction = distr(generator);

    int oldRow = getRow();
    int oldCol = getCol();

    bool canMove = (envPtr->checkGrid(direction, oldRow, oldCol));


    int newRow = oldRow;
    int newCol = oldCol;

    if (canMove) {
        // Environment function to set old grid coordinates to nullptr;
        // envPtr->setOldGridNull(oldRow, oldCol);

        setHasMoved(true);

        switch (direction) {
            case DOWN:
                newRow = oldRow + 1;
                break;
            case UP:
                newRow = oldRow - 1;
                break;
            case RIGHT:
                newCol = oldCol + 1;
                break;
            case LEFT:
                newCol = oldCol - 1;
                break;
        }

        envPtr->renderMovement(newRow, newCol, this); // function to set grid to grid[newRow][newCol]

    }

    if (breedCycle()) {
        breed();
    }
}

void Ant::breed() {

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

//                std::cout << "[ oldRow = " << getRow() << ", oldCol = " << getCol() << " ]" << std::endl;
            int newRow = getRow();
            int newCol = getCol();

            switch (direction) {
                case DOWN:
                    newRow = getRow() + 1;
                    break;
                case UP:
                    newRow = getRow() - 1;
                    break;
                case RIGHT:
                    newCol = getCol() + 1;
                    break;
                case LEFT:
                    newCol = getCol() - 1;
                    break;
            }

//            std::cout << "[ newRow = " << newRow << ", newCol = " << newCol << " ]" << std::endl;
            Organism *baby = new Ant("Ant", envPtr);
            baby->setHasMoved(true);
            envPtr->addToGridAt(newRow, newCol, baby);

            return;
//            std::cout << "Child: [ row = " << baby->getRow() << ", col = " << baby->getCol() << " ]" << std::endl;
        }
    }
}

