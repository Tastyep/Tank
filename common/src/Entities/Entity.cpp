#include "Entities/Entity.hh"
#include <iostream>

Entity::Entity(const sf::Sprite &sprite) : sprite(sprite) {
  auto bound = this->sprite.getGlobalBounds();

  this->sprite.setOrigin(bound.width / 2, bound.height / 2);
};

const Position &Entity::getPosition() const { return this->position; };
const sf::Sprite &Entity::getSprite() const { return this->sprite; };
void Entity::setPosition(Position pos) {
  this->sprite.setPosition(pos.x, pos.y);
  this->position = pos;
  this->spriteBound.translate(pos);
}

bool Entity::intersect(std::shared_ptr<Entity> ent) const {
  return this->spriteBound.intersects(ent->getSpriteCollisionObject());
}

void Entity::setSpriteCollisionObject(const SpriteCollision &spriteBound) {
  this->spriteBound = spriteBound;
}

const SpriteCollision &Entity::getSpriteCollisionObject() const {
  return this->spriteBound;
}
