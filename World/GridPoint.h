//
// Created by Roy Shefi on 23/11/2016.
//

#ifndef PART_2_GRIDPOINT_H
#define PART_2_GRIDPOINT_H

#include <iostream>
#include "vector"
#include "Point.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

/**
 * A rap for the point class for work in a grid.
 */

class GridPoint : public Point {
 private:
    bool visited;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & this->x;
        ar & this->y;
        ar & this->visited;
        ar & this->fa;
    }

 public:
    // The GridPoints father.
    GridPoint *fa;
    // Constructors.
    GridPoint(int a, int b);
    GridPoint();
    int x;
    int y;

  /**
   * Returns if the Grid point has been visited.
   * @return true if visited.
   */
  bool getState() { return this->visited; }

  /**
   * Compares the point to point a.
   * @param a -  point to compare to.
   * @return true if they are the same.
   */
  bool isEqual(GridPoint a);

  /**
   * Markes that the point has bees visited.
   */
  void changeState() { this->visited = true; }

  /**
   * Initializes the grid poit to false - not visited.
   */
  void initialize() { this->visited = false; }

  // Not useful now, Will be useful in the future.
  void getRouteToStart(GridPoint *g, vector<GridPoint> *an);

  /**
   * Assigns a father to the Grid point.   // Not useful now, Will be useful in the future.
   */
  void assignFather(GridPoint *f) { this->fa = f; }

  /**
   * Prints the gridPoint's father.   // Not useful now, Will be useful in the future.
   */
  void printFather() { cout << "(" << this->fa->x << "," << this->fa->y << ")" << endl; }

  void print() { cout << "(" << this->x << "," << this->y << ")" << endl; }

    /**
     * Copy function.
     * @return a copy of the grid point.
     */
    GridPoint * copy();
    bool operator==(const GridPoint& gb) {
        return this->isEqual(gb);
    }

};

#endif //PART_2_GRIDPOINT_H
