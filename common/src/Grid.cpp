#include "Grid.hh"
#include <iostream>
Grid::Grid(int width, int height) : width(width), height(height) {
  this->cells.resize(height);
  for (auto &cell : this->cells)
    cell.resize(width);
}

bool Grid::checkCollision(const Position &position, const Entity &entity) {
  Position cellPosition(position.x / 32, position.y / 32);

  std::cout << "cu: " << entity.getPosition().x << " " << entity.getPosition().y
            << " next: " << position.x << " " << position.y << " | "
            << cellPosition.x << " " << cellPosition.y << std::endl;
  if (cellPosition.x < 0 || cellPosition.y < 0 ||
      cellPosition.x >= this->width || cellPosition.y >= this->height)
    return true;
  auto &cell = this->getCell(cellPosition.x, cellPosition.y);
  auto &entities = cell.getObjects();
  auto &updatableEntities = cell.getMovableObjects();

  for (const auto &ent : entities) {
    if (&entity == ent.get())
      continue;
    if (entity.intersect(ent)) {
      return true;
    }
  }
  for (const auto &ent : updatableEntities) {
    if (&entity == ent.get())
      continue;
    if (entity.intersect(ent)) {
      return true;
    }
  }
  return false;
}

int Grid::getHeight() const { return this->height; }

int Grid::getWidth() const { return this->width; }

Cell &Grid::getCell(int x, int y) { return this->cells[y][x]; }