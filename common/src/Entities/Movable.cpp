#include "Entities/Movable.hh"

Movable::Movable(const sf::Sprite &sprite, double maxVelocity)
    : Entity(sprite), maxVelocity(maxVelocity), velocity(0), acceleration(0) {}

void Movable::update(std::chrono::nanoseconds time) {
  // double oldVelocity = this->velocity;
  //
  // this->velocity = std::min(oldVelocity + this->acceleration * time.count(),
  //                           this->maxVelocity);
  // this->position += time.count() * (oldVelocity + this->velocity) / 2.0;
}

void Movable::draw(sf::RenderTarget &renderTarget) const {
  renderTarget.draw(this->sprite);
}