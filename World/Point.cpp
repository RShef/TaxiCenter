//
// Created by Oded Thaller & Roey Shefi
//

#include "Point.h"

using namespace std;

int Point::getX() {
  return x;
}

int Point::getY() {
  return y;
}

void Point::setX(int a) {
  x = a;
}

void Point::setY(int b) {
  y = b;
}

void Point::print() {
  // Format required to print.
  cout << "(" << x << "," << y << ")";
}

Point::Point(int a, int b) {
  x = a;
  y = b;
}

Point::Point() {
  x = 0;
  y = 0;
}