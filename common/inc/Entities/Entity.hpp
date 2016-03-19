#ifndef TANK_ENTITY_HPP
#define TANK_ENTITY_HPP

#include "Position.hpp"
#include "TileIds.hpp"
#include <SFML/Graphics.hpp>

class Entity {
public:
  Entity(const sf::Sprite &sprite) : sprite(sprite){};

  ~Entity() = default;
  Entity(const Entity &other) = default;
  Entity(Entity &&other) = default;
  Entity &operator=(const Entity &other) = default;
  Entity &operator=(Entity &&other) = default;

  virtual bool intersect(const Entity &ent) const = 0;
  virtual void draw(sf::RenderTarget &renderTarget) const = 0;

  const Position &getPosition() const { return this->pos; };
  const sf::Sprite &getSprite() const { return this->sprite; };

protected:
  Position pos;
  sf::Sprite sprite;
};

#endif /* end of include guard: TANK_ENTITY_HPP */
