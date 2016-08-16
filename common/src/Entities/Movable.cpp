#include "Entities/Movable.hh"
#include "Grid.hh"
#include <iostream>

Movable::Movable(const EntityBody &body, const sf::Sprite &sprite,
                 double maxVelocity)
    : Entity(body, sprite), maxVelocity(maxVelocity), velocity(0),
      acceleration(0) {
  this->direction.x = std::cos(this->angle * radianConvert);
  this->direction.y = -std::sin(this->angle * radianConvert);
}

void Movable::rotate(double angle, Grid &grid) {
  double radianAngle;

  Entity::applyRotation(angle);
  if (grid.checkCollision(*this) == true) {
    Entity::applyRotation(-angle);
    return;
  }
  radianAngle = radianConvert * this->angle;
  this->direction.x = std::cos(radianAngle);
  this->direction.y = -std::sin(radianAngle);
}

void Movable::displace(int side, std::chrono::nanoseconds time, Grid &grid) {
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

void Movable::draw(sf::RenderTarget &renderTarget) const {
  renderTarget.draw(this->sprite);
  this->body.draw(renderTarget);
}

void Movable::setDirection(const sf::Vector2f direction) {
  this->direction = direction;
}
