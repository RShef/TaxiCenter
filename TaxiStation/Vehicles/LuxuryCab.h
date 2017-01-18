//
// Created by othaller on 01/12/16.
//

#ifndef PART_2_LUXURYCAB_H
#define PART_2_LUXURYCAB_H

#include "Cab.h"

class LuxuryCab : public Cab {

public:
    //default constructor
    LuxuryCab();

    /**
     * Costructor.
     * @param id - the cars id.
     * @param car - the type of cab.
     * @param color - thr cabs color.
     * @return /.
     */
    LuxuryCab(int id, Car car, Colors color);

    // Documentation as in father class - Cab.h.
    virtual double getPrice();
    virtual void move();
    virtual void addTrip(Trip*trip);

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Cab>(*this);
    }
};

#endif //PART_2_LUXURYCAB_H