//
// Created by Oded Thaller on 24/12/2016.
//

#include "../Socketing/Udp.h"
#include "Driver.h"
#include "Cab.h"
#include "Clock.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "Grid.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>

using namespace std;

BOOST_CLASS_EXPORT_GUID(StandardCab, "StandardCab");
BOOST_CLASS_EXPORT_GUID(LuxuryCab, "LuxuryCab");

/**
 * Find the status by Char given.
 * @param statusInput - Char input.
 * @return - the int value that the char represents.
 */
int findStatus(char statusInput) {
    if (statusInput == 'S') {
        return 0;
    } else if (statusInput == 'M') {
        return 1;
    } else if (statusInput == 'D') {
        return 2;
    } else {
        return 3;
    }
}

int main(int argc, char *argv[]) {

    int id, age, exp, cabId;
    char stat;
    char comma[4];
    char buffer[1024];
    Clock *clock = new Clock();

    //initialize UDP socket
    Udp udp(0, argv[1], atoi(argv[2]));
    udp.initialize();

    // Crate a new driver by user input.
    cin >> id >> comma[0] >> age >> comma[1] >> stat >> comma[2] >> exp >> comma[3] >> cabId;
    int status = findStatus(stat);
    Driver* driver = new Driver (id, age, (Driver::Status) status, exp, cabId);

    //send Driver to server
    stringstream ds;
    boost::archive::text_oarchive doa(ds);
    doa << driver;
    string buffer2 = ds.str();
    udp.sendData(buffer2);

    //receive cab from server and assign to driver
    stringstream cs;
    udp.receiveData(buffer, sizeof(buffer));
    cs << buffer;
    boost::archive::text_iarchive cia(cs);
    Cab *cab;
    cia >> cab;
    driver->addCab(cab);

    //receive map from server and add to driver
    stringstream ms;
    udp.receiveData(buffer, sizeof(buffer));
    ms << buffer;
    boost::archive::text_iarchive ia(ms);
    Grid *m;
    ia >> m;
    driver->addMap(m);

    //wait for "go", "trip" or "quit" command

    udp.receiveData(buffer, sizeof(buffer));

    // loop for moving drivers to destinations
    while (strcmp(buffer, "quit") != 0) {
        if (strcmp(buffer, "trip") == 0) {
            //receive trip from server and assign to driver
            stringstream ts;
            udp.receiveData(buffer, sizeof(buffer));
            ts << buffer;
            boost::archive::text_iarchive tia(ts);
            Trip *trip;
            tia >> trip;
            driver->getCab()->addTrip(trip);
            driver->setRoute();
        }
        if (strcmp(buffer, "go") == 0) {
            driver->moveOneStep();
            clock->advance();
        }
        udp.receiveData(buffer, sizeof(buffer));
    }

    udp.~Udp();
    return 0;
}