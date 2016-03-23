#include "Entities/Movable.hh"

Movable::Movable(const sf::Sprite &sprite, double maxVelocity)
    : Entity(sprite), maxVelocity(maxVelocity), velocity(0), acceleration(0) {

  auto bound =
      this->sprite.getGlobalBounds(); // your sprite size is equal to the
                                      // others' sprite size

  this->sprite.setOrigin(bound.width / 2, bound.height / 2);
}

void Movable::draw(sf::RenderTarget &renderTarget) const {
  renderTarget.draw(this->sprite);
}