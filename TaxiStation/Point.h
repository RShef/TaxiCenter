//
// Created by Oded Thaller & Roey Shefi
//

#ifndef PART_2_POINT_H
#define PART_2_POINT_H

#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sstream>


class Point {

 public:
    /**
     * Returns the 'x' of the point.
     * @return the 'x' of the point.
     */
    int getX();

    /**
     * Returns the 'y' of the point.
     * @return the 'y' of the point.
     */
    int getY();

    /**
     * Sets the 'x' of the point.
     * @param a - the value to set 'x' to.
     */
    void setX(int a);

    /**
     * Sets the 'y' value of the point.
     * @param b - the value to set 'y' to.
     */
    void setY(int b);

    /**
     * Prints the point.
     */
    void print();

    /**
     * Constructor.
     * @param a - 'x' value.
     * @param b - 'y' value.
     * @return /.
     */
    Point(int a, int b);

    /**
     * Constructor.
     * @return /.
     */
    Point();



protected:
  int x;
  int y;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & this->x;
        ar & this->y;
    }
};

#endif //PART_2_POINT_H
