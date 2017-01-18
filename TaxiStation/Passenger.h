//
// Created by Roy Shefi on 28/11/2016.
//

#ifndef PART_2_PASSENGER_H
#define PART_2_PASSENGER_H

#include "../World/GridPoint.h"

using namespace std;

class Passenger {

private:
    // The starting point of the passenger.
    GridPoint start;
    // The end point of the passenger.
    GridPoint end;
    // The passengers score.
    int score;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & this->start;
        ar & this->end;
        ar & this->score;
    }

public:
    //default constructor
    Passenger();
    /**
     * Constructor.
     * @param start - current location of the passenger.
     * @param end - destination of the passenger.
     * @return /.
     */
    Passenger(GridPoint start, GridPoint end);

    /**
     * Returns the current location of the passenger.
     * @return current location of the passenger.
     */
    GridPoint getStart();

    /**
     * Returns the destination of the passenger.
     * @return the destination of the passenger.
     */
    GridPoint getEnd();

    /**
     * Returns the passengers score.
     * @return the passengers score.
     */
    int getScore();
};

#endif //PART_2_PASSENGER_H