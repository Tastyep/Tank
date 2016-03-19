#include "Entities/Wall.hh"

Wall::Wall(const sf::Sprite &sprite) : Entity(sprite) {}

bool Wall::intersect(const Entity &ent) const {
  return false; // not done yet
}

void Wall::draw(sf::RenderTarget &renderTarget) const {
  renderTarget.draw(this->sprite);
}