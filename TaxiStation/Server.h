//
// Created by Roy Shefi on 15/01/2017.
//

#ifndef PART_2_SERVER_H
#define PART_2_SERVER_H

#include <iostream>
#include <pthread.h>
#include "GridPoint.h"
#include "TaxiCenter.h"
#include "Grid.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "Clock.h"
#include <boost/serialization/export.hpp>
#include "../Socketing/Socket.h"
#include <tcl.h>

using namespace std;

class Server : public Socket {
private:
    struct ClientData {
        int client_socket;
        int client;
        unsigned int client_size;
        bool online;
        char buffer[800000];
        Server* th;
        int driverIdC;
    };
    vector<char[]> *buff;
    pthread_mutex_t connection_locker;
    pthread_mutex_t list_locker;
    pthread_mutex_t connection_locker1;
    pthread_mutex_t list_locker1;
    char buffer[6000];
    string buffer2;
    int counter = 0;
    bool online;
    vector <Driver*> drivers;
    vector <Cab*> cabs;
    vector <Trip*> trips;
    vector <Socket*> clients;
    vector <GridPoint*> obstacles;
    TaxiCenter *tc;
    Clock *clock;
    vector<ClientData*> clientDis;
    Grid * m;
    vector<char*> *buff1;
    
 public:
    Server();

    Server(int po);
    
    void PreWork();

    void one(int numDrivers);

    void two(int id, int startX, int startY, int endX, int endY, int numPass, double tariff, int startTime);

    void three(int id, int type, int car, int color);

    void four(int id);

    void seven();

    void nine();

    static void* threadFunction(void* elm);

    //void setSocket(int po);

    void setUp(int x, int y, vector <GridPoint*> obstacles);

    //int sendData(string data);

    int initialize(){};

    int sendData(string data,int clientDescriptor);

    void acceptOneClient(ClientData* data);

    int receiveData(char* buffer, int size, int clientDescriptor, void* d);
    
    ClientData* findClientById(int id){
        for (int i = 0; i < this->clientDis.size(); i++) {
            if ( id == clientDis.at(i)->driverIdC){
                return clientDis.at(i);
            }
        }
    };
};

#endif //PART_2_SERVER_H
