#include "Entities/Movable.hh"
#include <iostream>
Movable::Movable(const sf::Sprite &sprite, double maxVelocity)
    : Entity(sprite), maxVelocity(maxVelocity), velocity(0), acceleration(0) {}

void Movable::rotate(double angle, Grid &grid) {
  double radianAngle;

  Entity::applyRotation(angle);
  if (grid.checkCollision(*this) == true) {
    Entity::applyRotation(-angle);
    return;
  }
  radianAngle = radianConvert * this->angle;
  this->direction.x = std::cos(radianAngle);
  this->direction.y = std::sin(radianAngle);
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
  auto edges = this->spriteBound.getBound().getEdges();

  sf::ConvexShape convex(4);
  for (unsigned int i = 0; i < edges.size(); ++i) {
    convex.setPoint(i, sf::Vector2f(edges[i].x, edges[i].y));
  }
  convex.setFillColor(sf::Color(0, 0, 0, 0));
  convex.setOutlineColor(sf::Color(255, 255, 255));
  convex.setOutlineThickness(1);
  renderTarget.draw(convex);
}