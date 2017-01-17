//
// Created by Roy Shefi on 28/11/2016.
//

#ifndef PART_2_TRIP_H
#define PART_2_TRIP_H

#include "Passenger.h"
#include "Map.h"
#include <boost/serialization/vector.hpp>
#include "Bfs.h"

using namespace std;

class Trip {
    //Test.
 private:
    // The trip id.
    int id;
    // The total distance gone so far in the trip.
    int distGone;
    // The start point of the trip.
    GridPoint* start;
    // The end point of the trip.
    GridPoint* end;
    // The number of passengers on the trip.
    int numPass;
    // The trips fair.
    double tariff;
    // The passengers on the trip.
    vector<Passenger*> pass;
    // If the trip is assigned to a driver.
    bool assigned;
    // if the trip is done
    bool done;
    // the time to start the trip
    int startTime;
    vector<GridPoint*>* route;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & this->id;
        ar & this->distGone;
        ar & this->start;
        ar & this->end;
        ar & this->numPass;
        ar & this->tariff;
        ar & this->pass;
        ar & this->assigned;
        ar & this->done;
        ar & this->startTime;
    }

public:
    Map *map;
    /**
     * Constructor.
     * @param id - trip id number.
     * @param start - start point of the trip.
     * @param end - end point of the trip.
     * @param numPass - number of passengers on the trip.
     * @param tariff - trips fair.
     * @param pass - The passengers on the trip.
     * @return /.
     */
    Trip(int id, GridPoint* start, GridPoint* end, int numPass, double tariff, vector<Passenger*> pass, int startTime);

    /**
     * Empty constructor.
     * @return /.
     */
    Trip();

    /**
     * Move to next point on the trip.
     */
    void move(bool isLux);

    /**
     * Return he distance gone so far.
     * @return the distance gone so far.
     */
    int getDisGone();

    int getStartTime();

    /**
     * Gets the cabs fair.
     * @param cabType - the type of cab.
     * @return the cabs fair.
     */
    double getFare(int cabType);

    /**
     * Returns the starting point of the trip.
     * @return the starting point of the trip.
     */
    GridPoint* getStart(){ return this->start;}

    /**
     * Returns the end point of the trip.
     * @return the end point of the trip.
     */
    GridPoint* getEnd(){ return this->end;}

    /**
     * Set trip as finished.
     */
    void setDone();

    /**
     * Check if the trip was finished.
     * @return true if trip completed.
     */
    bool isDone();

    bool isAssigned();

    void assign();
    void setMap (Map * m) { this->map = m;}
    vector<GridPoint*> *getRoute();
    static void* calRoute(void* elm);
    void prossRoute();
};

#endif //PART_2_TRIP_H