#include "Cell.hh"
#include <algorithm>

const std::vector<std::shared_ptr<Entity>> &Cell::getObjects() {
  return this->objects;
}

void Cell::removeObject(const Position &pos) {
  auto it = std::find_if(this->objects.begin(), this->objects.end(),
                         [&pos](std::shared_ptr<Entity> obj) {
                           return (obj->getPosition() == pos);
                         });
  if (it == this->objects.end())
    return;
  if (this->objects.size() > 1)
    std::swap(*it, this->objects.back());
  this->objects.pop_back();
}

void Cell::addObject(std::shared_ptr<Entity> object) {
  this->objects.push_back(object);
}