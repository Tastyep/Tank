#include "Entities/Ball.hh"
#include "Grid.hh"
#include <iostream>

Ball::Ball(const sf::Sprite &sprite) : Movable(sprite) {}

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