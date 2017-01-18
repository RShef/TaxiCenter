//
// Created by othaller on 01/12/16.
//

#ifndef PART_2_DRIVER_H
#define PART_2_DRIVER_H

#include "../World/Map.h"
#include "../World/Bfs.h"
//#include "Cab.h"

class Cab;
class Driver {

public:
    // The drivers status.
    enum Status{SINGLE, MARRIED, DIVORCED, WIDOWED};

    // Constructors.
    Driver();

    Driver(int i, int age,Status status, int exp, int cabId);

    /**
     * Returns the drivers location.
     * @return - The drivers location.
     */
    GridPoint* getLocation();

    /**
     * Adds the map to the driver.
     * @param map - the map of the world.
     */
    void addMap(Map *map);

    /**
     * Finds the route between his curent location to the end location of the trip using BFS.
     * @return A vector of points consisting the shortest path.
     */
    vector<GridPoint*> findRoute();

    /**
     * Notifys the driver time has passed.
     */
    void notifyTime();

    /**
     * Prints the drivers location.
     */
    void printLoc();

    /**
     * Returns the driver id.
     * @return the driver id.
     */
    int getId();

    /**
     * Moves the driver one step towards the end point
     */
    void moveOneStep();

    /**
     * Find the length of the shortest route via BFS from the drivers current location.
     * @param gr - the end point of the route.
     * @return the length of the route to gr.
     */
    int findShortRouteLen(GridPoint* gr);

    /**
    * Assigns a cab to the driver.
    */
    void addCab(Cab *cab);

    /**
     * Return the drivers cab.
     * @return the drivers cab.
     */
    Cab* getCab(){ return this->cabInfo;}

    void setRoute();

    int getCabId() { return this->cabId;}

private:
    // The driver id.
    int id;
    // The drivers age.
    int age;
    // The driver's marital status.
    Driver::Status status;
    // The drivers experience.
    int exp;
    int avgSat;
    int cabId;
    // The cab assigned to the driver.
    Cab *cabInfo;
    Map *map;
    // The drivers current location.
    GridPoint* currentLoc;
    // Driving route.
    vector<GridPoint*> route;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & this->id;
        ar & this->age;
        ar & this->status;
        ar & this->exp;
        ar & this->avgSat;
        ar & this->currentLoc;
        ar & this->cabId;

    }
};

#endif //PART_2_DRIVER_H