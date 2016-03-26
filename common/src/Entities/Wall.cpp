#include "Entities/Wall.hh"

Wall::Wall(const sf::Sprite &sprite) : Entity(sprite) {}

bool Wall::intersect(const Entity &ent) const {
  return false; // not done yet
}

void Wall::draw(sf::RenderTarget &renderTarget) const {
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