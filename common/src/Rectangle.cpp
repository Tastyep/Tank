#include "Rectangle.hh"
#include <limits>

Rectangle::Rectangle(const Position &tl, const Position &br)
    : Polygon({tl, {br.x, tl.y}, br, {tl.x, br.y}}) {
  this->width = br.x - tl.x;
  this->height = br.y - tl.y;
}

float Rectangle::getWidth() const { return this->width; }

float Rectangle::getHeight() const { return this->height; }
