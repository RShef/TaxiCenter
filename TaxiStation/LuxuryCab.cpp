//
// Created by othaller on 01/12/16.
//

#include "LuxuryCab.h"

LuxuryCab::LuxuryCab() {}

LuxuryCab::LuxuryCab(int id, Car car, Colors color) {
    this->id = id;
    this->kiloPassed = 0;
    this->car = car;
    this->color = color;
    this->isLux = true;
    this->trip = 0;
}

double LuxuryCab::getPrice() {
    return (*this->trip).getFare(2);
}

void LuxuryCab::move() {
    this->kiloPassed += 2;
}

void LuxuryCab::addTrip(Trip* trip) {
    this->trip = trip;
}