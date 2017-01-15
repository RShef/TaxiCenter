//
// Created by Roy Shefi on 15/01/2017.
//

#ifndef PART_2_SERVER_H
#define PART_2_SERVER_H
#include <iostream>
#include "../Socketing/Tcp.cpp"

#include "GridPoint.h"
#include "TaxiCenter.h"
#include "Grid.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "Clock.h"
#include <boost/serialization/export.hpp>

#include <tcl.h>

using namespace std;

//BOOST_CLASS_EXPORT_GUID(StandardCab, "StandardCab");
//BOOST_CLASS_EXPORT_GUID(LuxuryCab, "LuxuryCab");

class Server {
 public:
    /**
 * Find the type of car by Char given.
 * @param carInput - Char input.
 * @return - the int value that the char represents.
 */
    int findCar(char carInput) {
        if (carInput == 'H') {
            return 0;
        } else if (carInput == 'S') {
            return 1;
        } else if (carInput == 'T') {
            return 2;
        } else {
            return 3;
        }
    }


/**
 * Find the type of color of the car by Char given.
 * @param carInput - Char input.
 * @return - the int value that the char represents.
 */
    int findColor(char colorInput) {
        if (colorInput == 'R') {
            return 0;
        } else if (colorInput == 'B') {
            return 1;
        } else if (colorInput == 'G') {
            return 2;
        } else if (colorInput == 'P') {
            return 3;
        } else {
            return 4;
        }
    }
    pthread_mutex_t connection_locker1;
    pthread_mutex_t list_locker1;

    // input variables
    int gridX, gridY, numOfObstacles;
    int obsX, obsY;
    char comma[7];
    int task;
    int input1, input2, input3, input4, input5, input6, input7;
    char input8, input9;
    double input10;
    char buffer[6000];
    string buffer2;
    int counter = 0;
    bool online;

    // objects declarations
    vector <Driver*> drivers;
    vector <Cab*> cabs;
    vector <Trip*> trips;
    vector <Socket*> clients;
    vector <GridPoint*> obstacles;
    TaxiCenter *tc;
    Clock *clock = new Clock();
    vector<Tcp::ClientData*> clientDis;
    Grid * m;
    vector<char*> *buff1;

    void PreWork();
    Server(int x, int y, int ob);
    void one(int numOfDrivers);
    void two();
    void three();
    void four();
    void seven();
    void nine();
    static void* threadFunction(void* elm);

};

#endif //PART_2_SERVER_H
