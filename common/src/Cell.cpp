#include "Cell.hh"
#include <algorithm>

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

void Cell::addObject(std::shared_ptr<Movable> object) {
  this->movableObjects.push_back(object);
}

const std::vector<std::shared_ptr<Entity>> &Cell::getObjects() {
  return this->objects;
}

const std::vector<std::shared_ptr<Movable>> &Cell::getMovableObjects() {
  return this->movableObjects;
}

void Cell::removeDeadEntities() {
  this->movableObjects.erase(
      std::remove_if(this->movableObjects.begin(), this->movableObjects.end(),
                     [](auto ent) { return !ent->isAlive(); }),
      this->movableObjects.end());
}

void Cell::update(Grid &grid, std::chrono::nanoseconds time) {
  for (auto &obj : this->movableObjects) {
    if (obj->isAlive())
      obj->update(grid, time);
  }
  this->removeDeadEntities();
}
