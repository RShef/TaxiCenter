//
// Created by Roy Shefi on 15/01/2017.
//

#include "Server.h"

Server::Server(int x, int y, int ob) {
    this->m = new Grid(x, y);
    this->tc = new TaxiCenter();
    this->buff1 = new vector<char *>;
    if (ob > 0) {
        for (int i = 0; i < ob; ++i) {
            // Get input from user.
            cin >> obsX >> comma[0] >> obsY;
            obstacles.push_back(new GridPoint(obsX, obsY));
        }
    }
}
void* Server::threadFunction(void* elm) {
    Tcp::ClientData * d = (Tcp::ClientData*) elm;
    memset(d->buffer, 0, sizeof(d->buffer));
    d->tcp->receiveData(d->buffer, sizeof(d->buffer), d->client);
    //lock
    ((Server*)(d->th))->buff1->push_back(d->buffer);

}
void Server::one(int p) {
    Tcp *tcp = new Tcp(1,p);
    cin >> input1;
    Driver *d;
    //initialize clients UDPs
    tcp->initialize();

    for (int i = 0; i< input1; i++) {
        pthread_t thread;
        Tcp::ClientData *data = new Tcp::ClientData;
        tcp->acceptOneClient(data);

        pthread_mutex_lock(&list_locker1);
        clientDis.push_back(data);
        pthread_mutex_unlock(&list_locker1);

        memset(data->buffer, 0, sizeof(buffer));
        data->th = this;
        pthread_create(&thread, NULL, threadFunction, (void *) data);
        cout << data->buffer << endl;
    }
    // receive driver from client
    stringstream ds;
    //ds << data->buffer;
    boost::archive::text_iarchive ia(ds);
    ia >> d;
    drivers.push_back(d);
    tc->addDriver(d);
    d->addCab(tc->getCabById(d->getCabId()));
    tc->getDriverById(d->getId())->addMap(m);

    cout<<tc->getNumOfDrivers();
// UNtil here this needs to work.
    //send cabs to drivers
    stringstream cs;
    boost::archive::text_oarchive coa(cs);
    coa << cabs.at(1);
    buffer2 = cs.str();
    tc->getClients()->at(1)->sendData(buffer2);

    //send map to clients
    stringstream ms;
    boost::archive::text_oarchive oa(ms);
    oa << m;
    buffer2 = ms.str();
    tc->getClients()->at(1)->sendData(buffer2);
    d->addMap(m);
}
void Server::two() {
    cin >> input1 >> comma[0] >> input2 >> comma[1] >> input3 >> comma[2] >> input4
        >> comma[3] >> input5 >> comma[4] >> input6 >> comma[5] >> input10 >> comma[6] >> input7;
    GridPoint *start = new GridPoint (input2, input3);
    GridPoint *end = new GridPoint(input4, input5);
    vector<Passenger*> pass;
    // Create passengers.
    for (int i = 0; i < input6; ++i) {
        pass.push_back(new Passenger(*start, *end));
    }
    Trip *trip = new Trip(input1, start, end, input6, input10, pass, input7);
    // Add trip to the taxi center.
    tc->addTrip(trip);
    trips.push_back(trip);
    counter++;
}

void Server::three() {
    // input format: id, carType, manufacture, color
    cin >> input1 >> comma[0] >> input2 >> comma[1] >> input8 >> comma[2] >> input9;
    int car = findCar(input8);
    int color = findColor(input9);
    // Checking which type of cab it is.
    if (input2 == 1) {
        Cab *sc = new StandardCab(input1, (Cab::Car) car, (Cab::Colors) color);
        // Add cab to taxi center.
        tc->addCab(sc);
        cabs.push_back(sc);
    } else {
        Cab *lc = new LuxuryCab(input1, (Cab::Car) car, (Cab::Colors) color);
        tc->addCab(lc);
        cabs.push_back(lc);
    }

}

void Server::four() {
    cin >> input1;
    tc->printDriverLocById(input1);
}
void Server::seven() {
    delete(tc);
    delete(m);
    drivers.clear();
    cabs.clear();
    trips.clear();
    obstacles.clear();
    for (int i = 0; i < clients.size(); ++i) {
        clients.at(i)->sendData("quit");
        //clients.at(i)->~Udp();
    }
    clients.clear();

}
void Server::nine() {
    for (int i = 0; i < trips.size(); ++i) {
        // If the trip has not been assigned.
        if (clock->getTime() == trips.at(i)->getStartTime() - 1) {
            if (!trips.at(i)->isAssigned()) {
                // Get closest driver.
                Driver *temp = tc->whoIsClose(trips.at(i));
                temp->getCab()->addTrip(trips.at(i));
                temp->setRoute();
                //prepare client to receive trip
                tc->getClientById(temp->getId())->sendData("trip");
                //send trip to client
                stringstream ts;
                boost::archive::text_oarchive toa(ts);
                Trip *tt = trips.at(i);
                toa << tt;
                buffer2 = ts.str();
                tc->getClientById(temp->getId())->sendData(buffer2);
                // set trip as assigned
                trips.at(i)->assign();
            }
        }
    }
    tc->sendTaxi(clock->getTime());
    clock->advance();
}
void Server::PreWork() {

    // construct obstacles

}