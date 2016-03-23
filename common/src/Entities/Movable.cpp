#include "Entities/Movable.hh"

Movable::Movable(const sf::Sprite &sprite, double maxVelocity)
    : Entity(sprite), maxVelocity(maxVelocity), velocity(0), acceleration(0) {}

void Movable::draw(sf::RenderTarget &renderTarget) const {
  renderTarget.draw(this->sprite);
}