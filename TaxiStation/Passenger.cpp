//
// Created by Roy Shefi on 28/11/2016.
//

#include <cstdlib>
#include "Passenger.h"

Passenger::Passenger() {}

Passenger::Passenger(GridPoint start, GridPoint end) {
    this->start = start;
    this->end = end;
    this->score = 0;
}

GridPoint Passenger::getStart() {
    return this->start;
}

GridPoint Passenger::getEnd() {
    return this->end;
}

int Passenger::getScore() {
    this->score = rand() % 6;

    return this->score;
}


