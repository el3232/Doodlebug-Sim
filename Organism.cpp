//
// Created by Liza Leshchenko on 2019-07-05.
//

#include <string>
#include "Organism.h"
#include "Constants.h"
#include <random>
#include <iostream>

using namespace std;

Organism::Organism(std::string typeArg, Environment *envPtrArg, bool) : hasMoved(false) {
    type = typeArg;
    envPtr = envPtrArg;
    stepCounter = 0;
}

Organism::~Organism() = default;

int Organism::getRow() {
    return row;
}

int Organism::getCol() {
    return col;
}

std::string Organism::getType() {
    return type;
}

void Organism::setRow(int rowArg) {
    row = rowArg;
}

void Organism::setCol(int colArg) {
    col = colArg;
}

const Environment* Organism::getPtr() {
    return envPtr;
}

bool Organism::getHasMoved() {
    return hasMoved;
}

void Organism::setHasMoved(bool didMove) {
    hasMoved = didMove;
}


int Organism::getStepCount() {
    return stepCounter;
}

void Organism::incStepCount() {
    stepCounter += 1;
}

void Organism::getNewCellCoordinate(int direction, int &newRow, int &newCol) {
    switch (direction) {
        case DOWN:
            newRow = newRow + 1;
            break;
        case UP:
            newRow = newRow - 1;
            break;
        case RIGHT:
            newCol = newCol + 1;
            break;
        case LEFT:
            newCol = newCol - 1;
            break;
        default:
            break;
    }
}








