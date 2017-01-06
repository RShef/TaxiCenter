//
// Created by othaller on 01/12/16.
//

#include "StandardCab.h"

StandardCab::StandardCab() {}

StandardCab::StandardCab(int id, Car car, Colors color) {
    this->id = id;
    this->kiloPassed = 0;
    this->car = car;
    this->color = color;
    this->isLux = false;
}

void StandardCab::move() {
    this->kiloPassed += 1;
}

double StandardCab::getPrice() {
    return (*this->trip).getFare(1);
}

void StandardCab::addTrip(Trip* trip) {
    this->trip = trip;
}