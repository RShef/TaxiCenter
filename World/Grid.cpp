//
// Created by Oded Thaller on 22/11/2016.
//
#include "Map.h"
#include "Grid.h"
#include "Bfs.h"

using namespace std;

Grid::Grid() {}

Grid::Grid(int x, int y) {

  sizeX = x;
  sizeY = y;

  // Creates the map.
  map.resize(x);
  for (int i = 0; i < x; ++i) {
    map[i].resize(y);
  }

  for (int i = 0; i < x; ++i) {

    for (int j = 0; j < y; ++j) {

      map[i][j] = new GridPoint(i, j);

    }
  }
}

int Grid::getX() {
    return this->sizeX;
}

int Grid::getY() {
    return this->sizeY;
}

void Grid::printMap() {

  for (int i = sizeY - 1; i >= 0; --i) {

    for (int j = 0; j < sizeX; ++j) {

      (*map[j][i]).print();
    }

    cout << "\n";
  }
}

vector<GridPoint *> *Grid::getNeighbors(GridPoint p) {

    vector<GridPoint *> *vec = new vector<GridPoint *>;

    // Order of the clock - Right.
    if (p.x > 0) {
    (*vec).push_back(map[p.x - 1][p.y]);
    }
    // Up.
    if (p.y < sizeY - 1) {
    (*vec).push_back(map[p.x][p.y + 1]);
    }
    // Right.
    if (p.x < sizeX - 1) {
        (*vec).push_back(map[p.x + 1][p.y]);
    }
    // Down.
    if (p.y > 0) {
        (*vec).push_back(map[p.x][p.y - 1]);
    }

    return vec;
}

// Making everything false - NOT visited.
void Grid::initializeGridPoints() {
  for (int i = 0; i < map.size(); ++i) {

    for (int j = 0; j < map[i].size(); ++j) {

      (*map[i][j]).initialize();
    }
  }
}

// Copies the grid.
Map *Grid::copy() {
  return new Grid(this->sizeX, this->sizeY);
}
// De-constructor.
Grid::~Grid() {}
