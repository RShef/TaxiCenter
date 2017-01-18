//
// Created by othaller on 01/12/16.
//

#ifndef PART_2_TAXICENTER_H
#define PART_2_TAXICENTER_H

#include "Cab.h"
#include "Trip.h"
#include "Driver.h"
#include "../Socketing/Socket.h"
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class TaxiCenter {

private:
    // Number of cabs assigned to the taxi center.
    int numOfCabs;
    // Number of drivers assigned to the taxi center.
    int numOfDrivers;
    // The world map.
    Map *map;
    // The list of drivers added to the taxi center.
    vector<Driver*>* drivers;
    // The list of available drivers for a trip (NOT currently on a trip).
    vector<Driver*>* NotActiveDrivers;
    // Cabs assigned to the taxi center.
    vector<Cab *> *cabs;
    // The trips assigned to the taxi center.
    vector<Trip*>* trips;
    // clients (drivers) connected to this center.
    vector<Socket*>* clients;

public:
    /**
    * Constructor.
    * @param d - driver list.
    * @param c - cab list.
    */
    TaxiCenter(vector<Driver*>* d, vector<Cab *> *c);

    /**
     * Empty constructor.
     * @return /.
     */
    TaxiCenter();

    /**
    * Adding a real driver to the deposit of the taxi station.
    * @param dr - the driver (passed by address).
    */
    void addDriver(Driver* dr);

    /**
    * Adding a real cab to the deposit of the taxi station.
    * @param cb - the cab (passed by address).
    */
    void addCab(Cab * cb);

    void addClient(Socket* udp);

    vector <Socket*>* getClients();

    // Currently not used, will be in the future.
    void answerCall();

    /**
     * Sends ALL drivers to destination.
     */
    void sendTaxi(Driver *d);

    /**
    * Sends the map to all the drivers.
    */
    void sendMapToDrivers();

    /**
    * Adds the map to the taxi center.
    * @param m - the map given.
    */
    void addMap(Map* m);

    // Currently not used, will be in the future.
    void driverLoc(Driver drivers);

    /**
    * Prints the location of the driver by the id provided.
    * @param drId - the driver id to print.
    */
    void printDriverLocById(int driverId);

    // Currently not used, will be in the future.
    void notifyTime();

    // Currently not used, will be in the future.
    void getActiveDrivers();

    // Currently not used, will be in the future.
    vector<Driver *> * getStaticDrivers();

    // Currently not used, will be in the future.
    void cabLoc();

    /**
     * Adds trip 't' the the trips of the taxi center.
     * @param t - a trip.
     */
    void addTrip(Trip *t);

    /**
     * Finds the closest driver to the starting of the trip.
     * @param tr - a trip.
     * @return The closest driver to the statring point of the driver.
     */
    Driver* whoIsClose(Trip* tr);

    /**
    * Gets the cab that has the id given.
    * @param cabId - The cab id.
    * @return The real cab (by address).
    */
    Cab*getCabById (int cabId);

    /**
    * Gets the driver that has the id given.
    * @param drId - The id given.
    * @return The REAL driver that has the id.
    */
    Driver* getDriverById (int driverId);

    Socket* getClientById (int clId);

        /**
         * Returns the drivers avaliable to the taxi center.
         * @return The drivers avaliable to the taxi center.
         */
    vector <Driver*>* getDrivers();

    /**
     * Returns the cabs avaliable to the taxi center.
     * @return The cabs avaliable to the taxi center.
     */
    vector <Cab*>* getCabs();

    // Currently not used, will be in the future.
    Driver closestDriver(Trip trip, GridPoint g);

    // Currently not used, will be in the future.
    Trip createTrip();

    /**
     * Return number of drivers.
     * @return number of drivers.
     */
    int getNumOfDrivers();

    /**
     * Return number of cabs.
     * @return number of cabs.
     */
    int getNumOfCabs();

    void addCabToDriver();

};

#endif //PART_2_TAXICENTER_H