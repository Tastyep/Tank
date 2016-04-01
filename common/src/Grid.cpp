#include "Grid.hh"
#include <iostream>
Grid::Grid(int width, int height) : width(width), height(height) {
  this->cells.resize(height);
  for (auto &cell : this->cells)
    cell.resize(width);
}

bool Grid::checkCollision(const Entity &entity) {
  SpriteCollision spriteBound = entity.getSpriteCollisionObject();
  const Rectangle &rect = spriteBound.getBound();
  const auto &edges = rect.getEdges();
  std::array<Position, 4> cellPositions;
  unsigned int includedCells = 0;

  for (Position edge : edges) {
    edge.x = (int)edge.x / 32;
    edge.y = (int)edge.y / 32;
    cellPositions[includedCells] = edge;
    ++includedCells;
  }
  for (auto &cellPosition : cellPositions) {
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
  }
  return false;
}

int Grid::getHeight() const { return this->height; }

int Grid::getWidth() const { return this->width; }

Cell &Grid::getCell(int x, int y) { return this->cells[y][x]; }