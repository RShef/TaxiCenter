//
// Created by Roy Shefi on 26/01/2017.
//
#ifndef PART_2_TAXIWORLD_H
#define PART_2_TAXIWORLD_H
#include <iostream>
#include "../World/GridPoint.h"
#include "../TaxiStation/TaxiCenter.h"
#include "../World/Grid.h"
#include "ThreadPool.h"
#include "../TaxiStation/Vehicles/StandardCab.h"
#include "../TaxiStation/Vehicles/LuxuryCab.h"
#include "../World/Clock.h"
#include <boost/serialization/export.hpp>
#include "Server.h"
#include "../Logging/easylogging++.h"

class TaxiWorld {
 private:
    Server* server;
 public:
    TaxiWorld(Server* s);
    void setUp(int x, int y, vector <GridPoint*> obstacles);
    void getDriversFromClients(int d);
    void getDriver(int dr);
    void sendCabsToClients(int i);
    void sendMapToClients(int i);
    void sendTripToClients(int clientId, int i, Driver* dr);
    void addTrip(int id, int startX, int startY, int endX, int endY, int numPass, double tariff, int startTime);
    void addCab(int id, int type, int car, int color);
    int printDriver(int id);
    void close();
    void moveOnce();
    void moveClients();
    Grid *getMap() { return this->worldMap;}

    vector<char[]> *buff;
    pthread_mutex_t connection_locker;
    pthread_mutex_t list_locker;
    pthread_mutex_t connection_locker1;
    pthread_mutex_t list_locker1;
    char buffer[6000];
    string buffer2;
    int counter;
    bool online;
    vector <Driver*> drivers;
    vector <Cab*> cabs;
    vector <Socket*> clients;
    vector <GridPoint*> obstacles;
    TaxiCenter *tc;
    Clock *clock;
    vector<ClientData*> clientDis;
    Grid * worldMap;
    vector<char*> *buff1;
    pthread_t thread[10000];
    vector <Trip*> trips;
    ThreadPool* tp;
    vector<Job*> *jobs;



};

#endif //PART_2_TAXIWORLD_H
