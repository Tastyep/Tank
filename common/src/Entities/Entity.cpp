#include "Entities/Entity.hh"
#include "Entities/Ball.hh"
#include "Entities/Player.hh"
#include <iostream>

Entity::Entity(const sf::Sprite &sprite)
    : sprite(sprite), angle(0), alive(true) {
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

void Entity::move(const sf::Vector2f &displacement) {
  this->sprite.move(displacement);
  this->position += displacement;
  this->spriteBound.move(displacement);
}

void Entity::applyRotation(double angle) {
  this->angle += angle;
  if (this->angle >= 360)
    this->angle -= 360;
  else if (this->angle < 0)
    this->angle += 360;
  this->sprite.rotate(-angle);
  this->spriteBound.rotate(-angle);
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

bool Entity::isAlive() const { return this->alive; }

void Entity::setDead() { this->alive = false; }

void Entity::getImpacted(Ball &ball) {
  this->getImpacted(static_cast<Entity &>(ball));
}
void Entity::getImpacted(Player &player) {
  this->getImpacted(static_cast<Entity &>(player));
}
