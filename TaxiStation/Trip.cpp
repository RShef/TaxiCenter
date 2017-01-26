//
// Created by Roy Shefi on 28/11/2016.
//

#include "Trip.h"

Trip::Trip(int id, GridPoint* start, GridPoint* end, int numPass, double tariff, vector<Passenger*> pass, int startTime) {
    this->id = id;
    this->distGone = 0;
    this->start = start;
    this->end = end;
    this->numPass = numPass;
    this->tariff = tariff;
    this->pass = pass;
    this->done = false;
    this->assigned = false;
    this->startTime = startTime;
    this->cal = false;
    this->wrong = false;
}

Trip::Trip() {}

void Trip::move(bool isLux) {
    if (isLux) {
        this->distGone += 2;
    } else {
        this->distGone += 1;
    }
}

int Trip::getId() {
    return this->id;
}

int Trip::getDisGone() {
    return this->distGone;
}

int Trip::getStartTime() {
    return this->startTime;
}

double Trip::getFare(int cabType) {
    return this->tariff * cabType;
}

void Trip::setDone() {
    this->done = true;
}

bool Trip::isDone() {
    return done;
}

bool Trip::isAssigned() {
    return this->assigned;
}

void Trip::assign() {
    this->assigned = true;
}

void *Trip::calRoute(void *elm) {
    Trip* trip = (Trip*) elm;
    trip->prossRoute();
    trip->cal = true;
    return NULL;
}

vector<GridPoint *>* Trip::getRoute() {
    return this->route;
}

void Trip::prossRoute() {
    Bfs b(this->map);
    vector<GridPoint*>* vec = new vector<GridPoint*>;
    if(!b.findShortRoute(this->getStart(), this->getEnd(), vec)){
        this->route = NULL;
        this->wrong = true;
    }
    this->route = vec;
}
