//
// Created by Oded Thaller on 22/11/2016.
//

#ifndef PART_2_GRID_H
#define PART_2_GRID_H

#include <iostream>
#include <vector>
#include "Point.h"
#include "Map.h"
#include"GridPoint.h"

using namespace std;

class Grid : public Map {

 private:
  /**
   * the x size.
   */
    int sizeX;

  /**
   * the y size.
   */
    int sizeY;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & this->sizeX;
        ar & this->sizeY;
    }

 public:
  /**
   * the map.
   */
  vector<vector<GridPoint *> > map;

    Grid();
  // Creates a 2D grid of points of given size
  /**
   * Constructor.
   * @param x - sizeX.
   * @param y - sizeY.
   * @return No.
   */
  Grid(int x, int y);

  /**
   *Prints the grid where point (0,0) is on the bottom left
   */
  void printMap();

  /**
   * Takes a point, returns a vector of its up to 4 neighbors in clockwise order, from 9 o'clock
   * @param p
   * @return A vector of neighbors.
   */
  vector<GridPoint *> *getNeighbors(GridPoint p);

  /**
   * Makes 'visited' false.
   */
  void initializeGridPoints();

  /**
   *  Copy function.
   * @return - a copy of itself.
   */
  Map *copy();

  /**
   * Dconstructor.
   */
  ~Grid();
};

#endif //PART_2_GRID_H
