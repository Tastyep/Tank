#ifndef TANK_ENTITY_HPP
#define TANK_ENTITY_HPP

#include "EntityId.hpp"
#include "Position.hpp"
#include "TileManager.hh"
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity {
public:
  Entity(const sf::Sprite &sprite) : sprite(sprite) {
    auto bound = this->sprite.getGlobalBounds();
    this->sprite.setOrigin(bound.width / 2, bound.height / 2);
  };

  ~Entity() = default;
  Entity(const Entity &other) = default;
  Entity(Entity &&other) = default;
  Entity &operator=(const Entity &other) = default;
  Entity &operator=(Entity &&other) = default;

  virtual bool intersect(const Entity &ent) const = 0;
  virtual void draw(sf::RenderTarget &renderTarget) const = 0;

  const Position &getPosition() const { return this->position; };
  const sf::Sprite &getSprite() const { return this->sprite; };
  void setPosition(Position pos) {
    auto bound =
        this->sprite.getGlobalBounds(); // your sprite size is equal to the
                                        // others' sprite size
    this->position = pos;
    this->sprite.setPosition(pos.x * bound.width, pos.y * bound.height);
  }

protected:
  Position position;
  sf::Sprite sprite;
};

#endif /* end of include guard: TANK_ENTITY_HPP */
