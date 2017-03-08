//
// Created by Roy Shefi on 26/01/2017.
//

#include "TaxiWorld.h"
TaxiWorld::TaxiWorld(Server *s) : server(s) {


}
void TaxiWorld::setUp(int x, int y, vector<GridPoint *> obstacles) {
    this->worldMap = new Grid(x, y);
    LOG(INFO) << "Grid of " << x  << "X" << y << " created";
    this->tc = new TaxiCenter();
    this->buff1 = new vector<char *>;
    this->obstacles = obstacles;
    this->worldMap->obstacles = this->obstacles;
    this->jobs =  new vector<Job*>;
    this->tp = new ThreadPool(5);
    this->clock = new Clock();
    LOG(INFO) << obstacles.size() << " obstacles created";
}
void TaxiWorld::getDriversFromClients(int dr) {
    server->receiveMessages(dr);
    while (clientDis.size() < dr) {}
    for(int i = 0; i < dr; i++) {
        getDriver(i);
        sendCabsToClients(i);
        sendMapToClients(i);
    }
}

void TaxiWorld::getDriver(int i) {
    Driver *d;
    stringstream ds;
    ds << server->clientDis.at(i)->buffer;
    boost::archive::text_iarchive ia(ds);
    ia >> d;
    drivers.push_back(d);
    d->addMap(worldMap);
    LOG(INFO) << "Driver with ID " << d->getId() << " received";
    tc->addDriver(d);
    d->addCab(tc->getCabById(d->getCabId()));
    tc->getDriverById(d->getId())->addMap(worldMap);
    server->clientDis.at(i)->driverIdC = d->getId();
}
void TaxiWorld::sendCabsToClients(int i) {
//send cabs to drivers
    server->clientDis.at(i)->thisServer->sendData("cab", server->clientDis.at(i)->client);
    usleep(500000);
    stringstream cs;
    boost::archive::text_oarchive coa(cs);
    coa << cabs.at(i);
    buffer2 = cs.str();
    server->clientDis.at(i)->thisServer->sendData(buffer2, server->clientDis.at(i)->client);
    LOG(INFO) << "Cab " << cabs.at(i)->getId() << " sent to driver " << drivers.at(i)->getId();
    usleep(500000);
}
void TaxiWorld::sendMapToClients(int i) {
//send map to clients
    server->clientDis.at(i)->thisServer->sendData("map", server->clientDis.at(i)->client);
    usleep(500000);
    stringstream ms;
    boost::archive::text_oarchive oa(ms);
    oa << worldMap;
    buffer2 = ms.str();
    server->clientDis.at(i)->thisServer->sendData(buffer2, server->clientDis.at(i)->client);
    usleep(500000);
    LOG(INFO) << "Map sent to driver " << drivers.at(i)->getId();
}
void TaxiWorld::sendTripToClients(int clientId, int i, Driver* dr) {
    server->sendData("trip", clientId);
    usleep(500000);
    //send trip to client
    stringstream ts;
    boost::archive::text_oarchive toa(ts);
    Trip *tt = trips.at(i);
    toa << tt;
    buffer2 = ts.str();
    server->sendData(buffer2, clientId);
    usleep(500000);
    LOG(INFO) << "Trip " << tt->getId() << " sent to driver " << dr->getId();
}
void TaxiWorld::addTrip(int id, int startX, int startY, int endX, int endY, int numPass, double tariff, int startTime) {
    GridPoint *start = new GridPoint (startX, startY);
    GridPoint *end = new GridPoint(endX, endY);
    vector<Passenger*> pass;
    // Create passengers.
    for (int i = 0; i < numPass; ++i) {
        pass.push_back(new Passenger(*start, *end));
    }
    Trip *trip = new Trip(id, start, end, numPass, tariff, pass, startTime);
    LOG(INFO) << "New Trip with ID " << id << " created";
    trip->setMap(this->worldMap);
    // Multi thread work.
    Job *j = new Job(Trip::calRoute,(void*) trip);
    this->jobs->push_back(j);
    this->tp->addJob(j);
    LOG(INFO) << "New Job (Trip) added to thread pool";
    // Add trip to the taxi center.
    tc->addTrip(trip);
    trips.push_back(trip);
    counter++;
}
void TaxiWorld::addCab(int id, int type, int car, int color) {
// Checking which type of cab it is.
    if (type == 1) {
        Cab *sc = new StandardCab(id, (Cab::Car) car, (Cab::Colors) color);
        LOG(INFO) << "New Standard cab with ID " << id << " created";
        // Add cab to taxi center.
        tc->addCab(sc);
        cabs.push_back(sc);
    } else {
        Cab *lc = new LuxuryCab(id, (Cab::Car) car, (Cab::Colors) color);
        LOG(INFO) << "New Luxury cab with ID " << id << " created";
        tc->addCab(lc);
        cabs.push_back(lc);
    }
}
int TaxiWorld::printDriver(int id) {
    for (int i = 0; i < drivers.size(); ++i) {
        if (id == drivers.at(i)->getId()) {
            tc->printDriverLocById(id);
            return 0;
        }
    }
    LOG(ERROR) << "Driver does not exist. Please try again";
    cout << "-1" << endl;
    return -1;
}
void TaxiWorld::close() {
    server->quit();
    delete(tc);
    delete(worldMap);
    drivers.clear();
    cabs.clear();
    trips.clear();
    obstacles.clear();
    clients.clear();
}

void TaxiWorld::moveClients() {
    for (int i = 0; i < this->drivers.size(); ++i) {
        Driver *temp = this->drivers.at(i);
        if (temp->getCab()->getTrip() != NULL && !temp->getCab()->getTrip()->isDone()) {
            if (temp->getCab()->getTrip()->getStartTime() <= clock->getTime()) {
                int clientId = server->findClientById(temp->getId())->client;
                tc->sendTaxi(temp);
                server->sendData("go", clientId);
                usleep(500000);
            }
        }
    }
}

void TaxiWorld::moveOnce() {
    for (int i = 0; i < trips.size(); ++i) {
        // If the trip has not been assigned.
        if (clock->getTime() == trips.at(i)->getStartTime() - 1) {
            if (!trips.at(i)->isAssigned()) {
                // wait for trip.
                LOG(DEBUG) << "Starting trip calculation";
                while (!trips.at(i)->cal){
                    // Not good programing at all.
                }
                //pthread_join(thread[i],NULL);
                LOG(DEBUG) << "Trip calculation done";

                // Get closest driver.
                Driver *temp = tc->whoIsClose(trips.at(i));
                temp->getCab()->addTrip(trips.at(i));
                temp->setRoute();
                //prepare client to receive trip
                int clientId = server->findClientById(temp->getId())->client;
                sendTripToClients(clientId,i,temp);
                // set trip as assigned
                trips.at(i)->assign();
            }
        }
    }
    moveClients();
    clock->advance();
}

