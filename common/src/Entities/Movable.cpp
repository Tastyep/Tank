#include "Entities/Movable.hh"
#include <iostream>
Movable::Movable(const sf::Sprite &sprite, double maxVelocity)
    : Entity(sprite), maxVelocity(maxVelocity), velocity(0), acceleration(0) {}

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