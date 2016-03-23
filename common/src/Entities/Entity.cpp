#include "Entities/Entity.hh"
#include <iostream>

Entity::Entity(const sf::Sprite &sprite) : sprite(sprite) {
  auto bound = this->sprite.getGlobalBounds();
};

const Position &Entity::getPosition() const { return this->position; };
const sf::Sprite &Entity::getSprite() const { return this->sprite; };
void Entity::setPosition(Position pos) {
  auto bound =
      this->sprite.getGlobalBounds(); // your sprite size is equal to the
                                      // others' sprite size
  this->position = pos;
  this->sprite.setPosition(pos.x, pos.y);
}

bool Entity::intersect(std::shared_ptr<Entity> ent) const { return true; }