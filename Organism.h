//
// Created by Liza Leshchenko on 2019-07-05.
//

#pragma once
#include <string>
#include "Environment.h"
class Environment;

class Organism {
private:
    int row{};
    int col{};
    std::string type;
    bool hasMoved;
    int stepCounter;

protected:
    Environment *envPtr{};

public:

// CONSTRUCTOR: initializes Organism with a type, a pointer to its Environment, and the knowledge that it hasn't moved yet
    Organism(std::string typeArg, Environment *envPtrArg, bool movedArg);

/* DESTRUCTOR: necessary because we are using envPtr (pointer to Organism's Environment)
   copy constructor and assignment operator unused */

    virtual ~Organism();                                  // destructor

    int getRow();

    int getCol();

    void setRow(int);

    void setCol(int);

    bool getHasMoved();

    void setHasMoved(bool);

    virtual std::string getType();

    const Environment *getPtr();

    int getStepCount();

    static void getNewCellCoordinate(int direction, int &newRow, int &newCol);

    void incStepCount();

    virtual void move() = 0;

    virtual void breed() = 0;


};


