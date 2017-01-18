//
// Created by othaller on 01/12/16.
//

#include "TaxiCenter.h"

TaxiCenter::TaxiCenter(vector<Driver*>* d,vector<Cab*>* c) {}

TaxiCenter::TaxiCenter(){
    this->drivers = new vector<Driver*>;
    this->cabs = new vector<Cab*>;
    this->clients = new vector<Socket*>;
    this->numOfCabs = 0;
    this->numOfDrivers = 0;
    this->trips = new vector<Trip*>;
    this->NotActiveDrivers = new vector<Driver*>;
}

void TaxiCenter::addDriver(Driver* dr) {
    (*this->drivers).push_back(dr);
    (*this->NotActiveDrivers).push_back(dr);
    this->numOfDrivers += 1;
}

void TaxiCenter::addCab(Cab* cb) {
    (*this->cabs).push_back(cb);
    this->numOfCabs += 1;
}

void TaxiCenter::addClient(Socket* udp) {
    (*this->clients).push_back(udp);
}

vector <Socket*>* TaxiCenter::getClients() {
    return this->clients;
}

void TaxiCenter::answerCall() {

}

void TaxiCenter::sendTaxi(Driver *d) {

    d->moveOneStep();

    // Return the driver and cab to the available drivers list for future trips if trip is done
    if (d->getCab()->getTrip()->isDone()) {
        (*this->NotActiveDrivers).push_back(d);
    }
}

void TaxiCenter::addMap(Map* m) {
    this->map = m;
}

void TaxiCenter::sendMapToDrivers() {
    for (int i = 0; i < (*this->drivers).size(); ++i) {
        (*this->drivers).at(i)->addMap(this->map);
    }
}

void TaxiCenter::printDriverLocById(int drId) {
    for (int i =0; i< (*this->drivers).size(); i ++) {
        if((*this->drivers).at(i)->getId() == drId) {
            (*this->drivers).at(i)->printLoc();
        }
    }
}

void TaxiCenter::notifyTime() {

}

void TaxiCenter::getActiveDrivers() {

}

vector<Driver *> * TaxiCenter::getStaticDrivers() {
    return this->NotActiveDrivers;

}

void TaxiCenter::cabLoc() {

}

void TaxiCenter::driverLoc(Driver drivers) {

}

vector<Driver *>* TaxiCenter::getDrivers() {
    return drivers;
}

vector<Cab *>* TaxiCenter::getCabs() {
    return cabs;
}

Cab* TaxiCenter::getCabById (int cabId){
    for (int i =0; i< (*this->cabs).size(); i ++) {
        if((*this->cabs).at(i)->getId() == cabId) {
            return (*this->cabs).at(i);
        }
    }
}

Driver* TaxiCenter::getDriverById (int drId) {
    for (int i =0; i< (*this->drivers).size(); i ++) {
        if((*this->drivers).at(i)->getId() == drId) {
            return (*this->drivers).at(i);
        }
    }
}

Socket* TaxiCenter::getClientById (int clId) {
    for (int i =0; i< (*this->drivers).size(); i ++) {
        if((*this->drivers).at(i)->getId() == clId) {
            return (*this->clients).at(i);
        }
    }
}

int TaxiCenter::getNumOfDrivers() {
    return this->numOfDrivers;
}

int TaxiCenter::getNumOfCabs() {
    return this->numOfCabs;
}

void TaxiCenter::addTrip(Trip *t) {
    this->trips->push_back(t);
}

Driver *TaxiCenter::whoIsClose(Trip *tr) {
    int max =0;
    int a = 0;
    // For all available drivers.
    for (int i =0; i< (*this->NotActiveDrivers).size(); i ++) {
        // Who ever has the shortest route.
        // if equal then the first driver that arrived at the starting point.
        int t =(*this->NotActiveDrivers).at(i)->findShortRouteLen(tr->getEnd());
        if(t>max){
            max = t;
            a = i;
        }
    }
    Driver*tt =(*this->NotActiveDrivers).at(a);
    // Erase the driver from the available driver list.
    this->NotActiveDrivers->erase(this->NotActiveDrivers->begin()+a);
    return tt;
}

