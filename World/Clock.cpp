//
// Created by othaller on 29/12/16.
//

#include "Clock.h"

Clock::Clock() {
    this->time = 0;
}

int Clock::getTime() {
    return this->time;
}

void Clock::advance() {
    this->time++;
}
