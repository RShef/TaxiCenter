//
// Created by othaller on 01/12/16.
//

#ifndef PART_2_STANDARDCAB_H
#define PART_2_STANDARDCAB_H

#include "Cab.h"

class StandardCab : public  Cab {

public:
    //default constructor
    StandardCab();

    /**
     * Constructor.
     * @param id - the cabs id.
     * @param car - the type of cab.
     * @param color - the cabs color.
     * @return /.
     */
    StandardCab(int id, Car car, Colors color);

    // Documentation as in father class - Cab.h.
    virtual void move();
    virtual double getPrice();
    virtual void addTrip(Trip* trip);

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Cab>(*this);
    }
};

#endif //PART_2_STANDARDCAB_H