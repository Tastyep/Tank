#include "Entities/Ball.hh"
#include "Entities/Player.hh"
#include "Entities/Wall.hh"
#include "Grid.hh"
#include <iostream>

Ball::Ball(const sf::Sprite &sprite)
    : Movable(sprite), bounceCount(0), maxBounce(5) {}

void Ball::displace(int side, std::chrono::nanoseconds time, Grid &grid) {
  sf::Vector2f displacement;

  this->acceleration = side;
  this->velocity = std::min(this->velocity + this->acceleration * time.count(),
                            this->maxVelocity);
  this->velocity = std::max(this->velocity, -this->maxVelocity);
  displacement.x = this->velocity * time.count() * this->direction.x;
  displacement.y = this->velocity * time.count() * this->direction.y;

  this->move(displacement);
  if (grid.checkCollision(*this) == true)
    this->move(-displacement);
}

void Ball::update(Grid &grid, std::chrono::nanoseconds time) {
  this->displace(1, time, grid);
}

void Ball::getImpacted(Entity &entity, const intersectionResult &inter) {}

void Ball::impact(std::shared_ptr<Entity> entity,
                  const intersectionResult &inter) {
  entity->getImpacted(*this, inter);
}

void Ball::bounce() {
  ++this->bounceCount;
  if (this->bounceCount > this->maxBounce)
    this->alive = false;
}

void Ball::computeReflectedDirection(const Wall &wall,
                                     const intersectionResult &inter) {
  // V’ = V – (2 * (V . N)) * N
  sf::Vector2f scaledNormal = inter.faceNormal;
  float dot = this->direction.x * inter.faceNormal.x +
              this->direction.y * inter.faceNormal.y;

  scaledNormal.x *= (2.f * dot);
  scaledNormal.y *= (2.f * dot);
  this->direction -= scaledNormal;
  std::cout << "normal: " << inter.faceNormal.x << " " << inter.faceNormal.y
            << "\n";
}