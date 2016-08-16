#include "Grid.hh"
#include <array>
#include <functional>

Grid::Grid(int width, int height) : width(width), height(height) {
  this->cells.resize(height);
  for (auto &cell : this->cells)
    cell.resize(width);
}

bool Grid::checkCollision(Movable &entity) {
  const Rectangle &rect = entity.getBody().getBound();
  const auto &edges = rect.getVertices();
  std::array<Position, 4> cellPositions;
  unsigned int includeCells = 0;
  intersectionResult inter;
  bool isIncluded;

  for (const Position &edge : edges) {
    Position cellPos((int)edge.x / 32, (int)edge.y / 32);
    isIncluded = false;

    for (unsigned int i = 0; i < includeCells; ++i) {
      if (cellPositions[i] == cellPos) {
        isIncluded = true;
        break;
      }
    }
    if (!isIncluded)
      cellPositions[includeCells++] = cellPos;
  }
  for (unsigned int i = 0; i < includeCells; ++i) {
    const auto &cellPosition = cellPositions[i];

    if (cellPosition.x < 0 || cellPosition.y < 0 ||
        cellPosition.x >= this->width || cellPosition.y >= this->height)
      return true;
    auto &cell = this->getCell(cellPosition.x, cellPosition.y);
    auto &entities = cell.getObjects();
    auto &updatableEntities = cell.getMovableObjects();

    for (auto &ent : entities) {
      if (&entity == ent.get() || !ent->isAlive()) {
        continue;
      }
      inter = this->intersectionCalculator.testIntersection(entity.getBody(),
                                                            ent->getBody());
      if (inter.intersects) {
        entity.impact(ent, inter);
        return true;
      }
    }
    for (auto &ent : updatableEntities) {
      if (&entity == ent.get() || !ent->isAlive())
        continue;
      inter = this->intersectionCalculator.testIntersection(entity.getBody(),
                                                            ent->getBody());
      if (inter.intersects) {
        entity.impact(ent, inter);
        return true;
      }
    }
  }
  return false;
}

int Grid::getHeight() const { return this->height; }

int Grid::getWidth() const { return this->width; }

Cell &Grid::getCell(int x, int y) { return this->cells[y][x]; }

void Grid::addObjectToQueue(std::shared_ptr<Entity> object) {
  this->objects.push(object);
}

void Grid::addObjectToQueue(std::shared_ptr<Movable> object) {
  this->movableObjects.push(object);
}

void Grid::processQueue() {
  while (!this->objects.empty()) {
    std::shared_ptr<Entity> object = this->objects.front();
    const auto &bound = object->getSprite().getGlobalBounds();
    const Position &position = object->getPosition();

    this->getCell(position.x / bound.width, position.y / bound.height)
        .addObject(object);
    this->objects.pop();
  }
  while (!this->movableObjects.empty()) {
    std::shared_ptr<Movable> object = this->movableObjects.front();
    const auto &bound = object->getSprite().getGlobalBounds();
    const Position &position = object->getPosition();

    this->getCell(position.x / bound.width, position.y / bound.height)
        .addObject(object);
    this->movableObjects.pop();
  }
}
