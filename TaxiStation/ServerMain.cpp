//
// Created by Oded Thaller on 11/12/2016.
//

#include <iostream>
#include "../Socketing/Udp.h"
#include "GridPoint.h"
#include "TaxiCenter.h"
#include "Grid.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "Clock.h"
#include <vector>
#include <boost/serialization/export.hpp>

using namespace std;

BOOST_CLASS_EXPORT_GUID(StandardCab, "StandardCab");
BOOST_CLASS_EXPORT_GUID(LuxuryCab, "LuxuryCab");

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

int main(int argc, char *argv[]) {

    // input variables
    int gridX, gridY, numOfObstacles;
    int obsX, obsY;
    char comma[7];
    int task;
    int input1, input2, input3, input4, input5, input6, input7;
    char input8, input9;
    double input10;
    char buffer[1024];
    string buffer2;
    int counter = 0;

    // objects declarations
    vector <Driver*> drivers;
    vector <Cab*> cabs;
    vector <Trip*> trips;
    vector <Udp*> clients;
    vector <GridPoint*> obstacles;
    TaxiCenter *tc;
    Clock *clock = new Clock();

    // Create THE Taxi Center.
    tc = new TaxiCenter();
    Grid *m;

    // construct the grid (our WORLD).
    cin >> gridX >> gridY >> numOfObstacles;
    m = new Grid(gridX, gridY);

    // construct obstacles
    if (numOfObstacles > 0) {
        for (int i = 0; i < numOfObstacles; ++i) {
            // Get input from user.
            cin >> obsX >> comma[0] >> obsY;
            obstacles.push_back(new GridPoint(obsX, obsY));
        }
    }

    // run tasks loop
    cin >> task;

    while (task != 0) {

        switch (task) {

            case 1: //receive drivers from clients
            {
                // input format: number drivers to expect
                cin >> input1;
                Driver *d;
                int port = atoi(argv[1]);
                for (int i = 0; i < input1; i++) {
                    Udp *udp = new Udp(1, port + i);
                    //initialize clients UDPs
                    udp->initialize();
                    clients.push_back(udp);
                    tc->addClient(udp);

                    // receive driver from client
                    stringstream ds;
                    tc->getClients()->at(i)->receiveData(buffer, sizeof(buffer));
                    ds << buffer;
                    boost::archive::text_iarchive ia(ds);
                    ia >> d;
                    drivers.push_back(d);
                    tc->addDriver(d);
                    d->addCab(cabs.at(i));
                    tc->getDriverById(d->getId())->addMap(m);

                    //send cabs to drivers
                    stringstream cs;
                    boost::archive::text_oarchive coa(cs);
                    coa << cabs.at(i);
                    buffer2 = cs.str();
                    tc->getClients()->at(i)->sendData(buffer2);

                    //send map to clients
                    stringstream ms;
                    boost::archive::text_oarchive oa(ms);
                    oa << m;
                    buffer2 = ms.str();
                    tc->getClients()->at(i)->sendData(buffer2);
                    d->addMap(m);
                }
                break;
            }

            case 2: // insert new trip
            {
                // input format: id, startX, startY, endX, endY, numOfPass, tariff, start time
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
                break;
            }

            case 3: // insert new vehicle
            {
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
                break;
            }

            case 4: // request driver location bt id and print it.
            {
                // User input.
                cin >> input1;
                tc->printDriverLocById(input1);
                break;
            }

            case 9: // send trips and move one step
            {
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
                break;
            }

            case 7: // clean up and exit
            {
                delete(tc);
                delete(m);
                drivers.clear();
                cabs.clear();
                trips.clear();
                obstacles.clear();
                for (int i = 0; i < clients.size(); ++i) {
                    clients.at(i)->sendData("quit");
                    clients.at(i)->~Udp();
                }
                clients.clear();
                return 0;
            }
            default: {
                break;
            }
        }

        cin >> task;
    }
}