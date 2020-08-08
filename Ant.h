//
// Created by Liza Leshchenko on 2019-07-05.
//

#ifndef EL3232_HW13_DOODLEBUG_ANT_H
#define EL3232_HW13_DOODLEBUG_ANT_H



#include "Organism.h"
#include "Environment.h"
#include <string>


class Ant: public Organism {
//    Ant() : Organism(std::string(), nullptr, false) {}

private:
    //empty
public:
//        Ant();
    Ant(const std::string& type, Environment* ptrEnv);

    bool breedCycle();

    virtual void move();
    virtual void breed();

};



#endif //EL3232_HW13_DOODLEBUG_ANT_H
