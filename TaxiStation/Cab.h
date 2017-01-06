//
// Created by Roy Shefi on 28/11/2016.
//

#ifndef PART_2_CAB_H
#define PART_2_CAB_H

#include <iostream>
#include "Driver.h"
#include "GridPoint.h"
#include "Trip.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;
class Driver;

class Cab {
public:
    // Car type.
    enum Car { HONDA, SUBARU, TESLA, FIAT };
    // Car color.
    enum Colors { RED, BLUE, GREEN, PINK, WHITE };
    /**
     * Returns car price.
     * @return - car price.
     */
    virtual double getPrice() = 0;
    /**
     * Moves the cab.
     */
    virtual void move() = 0;
    /**
     * Assigns a trip to the cab.
     * @param trip - a trip.
     */
    virtual void addTrip(Trip* trip) = 0;
    /**
     * Returns the cabs trip.
     * @return - the cabs trip.
     */
    Trip* getTrip() {return this->trip;}
    /**
     * Returns the cabs id.
     * @return - the cab id.
     */
    int getId() { return this->id;}
    /**
     * Retuens the kilometers passed.
     * @return - The kilometors passed by the cab.
     */
    int getKiloPassed() const {
        return kiloPassed;
    }
    /**
     *
     * @return
     */
    bool getType() {return this->isLux;}

protected:
    // Cab id.
    int id;
    // Distance driven in the cab.
    int kiloPassed;
    // is the cab a standard or luxury cab
    bool isLux;
    // The type pf car.
    Car car;
    // The color of the car.
    Colors color;
    // The trip the cab needs to do.
    Trip *trip;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & this->car;
        ar & this->color;
        ar & this->id;
        ar & this->isLux;
        ar & this->kiloPassed;
        ar & this->trip;
    }

};

#endif //PART_2_CAB_H