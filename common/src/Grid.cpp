#include "Grid.hh"

Grid::Grid(int width, int height) : width(width), height(height) {
  this->cells.resize(height);
  for (auto &cell : this->cells)
    cell.resize(width);
}

int Grid::getHeight() const { return this->height; }

int Grid::getWidth() const { return this->width; }

Cell &Grid::getCell(int x, int y) { return this->cells[y][x]; }