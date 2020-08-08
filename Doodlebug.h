//
// Created by Liza Leshchenko on 2019-07-05.
//

#ifndef ENVANTDOODLE_SIM_DOODLEBUG_H
#define ENVANTDOODLE_SIM_DOODLEBUG_H


#include "Organism.h"
#include "Environment.h"
#include <string>

class Doodlebug : public Organism {
private:
    int starveCount;

public:
    Doodlebug(std::string type, Environment *ptrEnv);

    void incStarveCount();

    void resetStarveCount();

    bool eat();

    virtual bool breedCycle();

    void tryToMove();

    virtual void move();

    virtual void breed();

};


#endif //ENVANTDOODLE_SIM_DOODLEBUG_H
