//
// Created by othaller on 01/12/16.
//

#include "Driver.h"
#include "Vehicles/Cab.h"
#include "../Logging/easylogging++.h"

Driver::Driver(int i, int age, Status status, int exp, int cabId) {

    this->id = i;
    this->age = age;
    this->status = status;
    this->exp = exp;
    this->avgSat = 0;
    this->cabInfo = 0;
    this->currentLoc = new GridPoint(0,0);
    this->cabId = cabId;
}

Driver::Driver() {}

vector<GridPoint*> Driver::findRoute() {
    return *cabInfo->getTrip()->getRoute();
}

void Driver::moveOneStep() {
    if (this->getCab()->getType() && this->route.size() >= 3) {
        currentLoc = this->route.at(2);
        this->route.erase(this->route.begin(), this->route.begin()+2);
    } else {
        currentLoc = this->route.at(1);
        this->route.erase(this->route.begin());
    }
    LOG(DEBUG) << "driver " << this->id << " moved to " << this->currentLoc->x << "," << this->currentLoc->y;
    this->getCab()->move();
    this->getCab()->getTrip()->move(this->getCab()->getType());
    // Mark Trip as done if arrived at destination
    if (this->getCab()->getTrip()->getEnd()->isEqual(*this->getLocation())) {
        this->getCab()->getTrip()->setDone();
    }
}

GridPoint* Driver::getLocation() {
    return this->currentLoc;
}

int Driver::findShortRouteLen(GridPoint *gr) {
    if ((*gr).isEqual(*(this->currentLoc))) {
        return 0;
    } else {
        Bfs b(this->map);
        vector<GridPoint*>* vec = new vector<GridPoint*>;
        b.findShortRoute(this->currentLoc, gr, vec);
        return (int)vec->size();
    }
}

void Driver::addMap(Map* map) {
    this->map = map;
}

void Driver::notifyTime() {

}

void Driver::printLoc() {
    (*currentLoc).print();
}

int Driver::getId() {
    return this->id;
}

void Driver::addCab(Cab *cab) {
    this->cabInfo = cab;
}

void Driver::setRoute() {
    this->route = findRoute();
}
