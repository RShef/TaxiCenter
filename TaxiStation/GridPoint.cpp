//
// Created by Roy Shefi on 23/11/2016.
//

#include <iostream>
#include "Point.h"
#include "Map.h"

using namespace std;

GridPoint::GridPoint(int a, int b) {
  this->fa = 0;
  this->visited = false;
  this->x = a;
  this->y = b;
}

GridPoint::GridPoint() {
  this->x = 0;
  this->y = 0;

}

bool GridPoint::isEqual(GridPoint a) {
  return a.x == this->x && a.y == this->y;
}
GridPoint *GridPoint::copy() {
    return new GridPoint(this->x,this->y);
}
// Will be useful in the future.
void GridPoint::getRouteToStart(GridPoint *g, vector<GridPoint> *an) {

  (*an).push_back(*g);
  if ((g) == 0) {
    return;
  }

  getRouteToStart((*g).fa, an);


}
