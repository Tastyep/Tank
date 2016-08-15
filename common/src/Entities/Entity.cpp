#include "Entities/Entity.hh"
#include "Entities/Ball.hh"
#include "Entities/Player.hh"
#include <iostream>

Entity::Entity(const EntityBody &body, const sf::Sprite &sprite)
    : body(body), angle(0), sprite(sprite), alive(true) {
  auto bound = this->sprite.getGlobalBounds();

  this->sprite.setOrigin(bound.width / 2, bound.height / 2);
};

const Position &Entity::getPosition() const { return this->position; };
const sf::Sprite &Entity::getSprite() const { return this->sprite; };

void Entity::setPosition(Position pos) {
  this->sprite.setPosition(pos.x, pos.y);
  this->position = pos;
  this->body.setPosition(pos);
}

void Entity::move(const sf::Vector2f &displacement) {
  this->sprite.move(displacement);
  this->position += displacement;
  this->body.move(displacement);
}

void Entity::applyRotation(double angle) {
  this->angle += angle;
  if (this->angle >= 360)
    this->angle -= 360;
  else if (this->angle < 0)
    this->angle += 360;
  this->sprite.rotate(-angle);
  this->body.rotate(-angle);
}

void Entity::setBody(const EntityBody &body) { this->body = body; }

const EntityBody &Entity::getBody() const { return this->body; }

bool Entity::isAlive() const { return this->alive; }

void Entity::setDead() { this->alive = false; }

void Entity::getImpacted(Ball &ball, const intersectionResult &inter) {
  this->getImpacted(static_cast<Entity &>(ball), inter);
}
void Entity::getImpacted(Player &player, const intersectionResult &inter) {
  this->getImpacted(static_cast<Entity &>(player), inter);
}
