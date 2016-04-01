#ifndef TANK_ENTITY_HPP
#define TANK_ENTITY_HPP

#include "EntityId.hpp"
#include "Position.hpp"
#include "SpriteCollision.hh"
#include "TileManager.hh"
#include <SFML/Graphics.hpp>
#include <memory>

class Entity {
public:
  static constexpr auto pi = std::acos(-1);
  static constexpr double radianConvert = (pi / 180.0);

public:
  Entity(const sf::Sprite &sprite);

  ~Entity() = default;
  Entity(const Entity &other) = default;
  Entity(Entity &&other) = default;
  Entity &operator=(const Entity &other) = default;
  Entity &operator=(Entity &&other) = default;

  virtual void draw(sf::RenderTarget &renderTarget) const = 0;

  virtual bool intersect(std::shared_ptr<Entity> ent) const;
  const Position &getPosition() const;
  const sf::Sprite &getSprite() const;
  void setPosition(Position pos);
  void move(const sf::Vector2f &displacement);
  void applyRotation(double angle);
  void setSpriteCollisionObject(const SpriteCollision &spriteBound);
  const SpriteCollision &getSpriteCollisionObject() const;

protected:
  Position position;
  sf::Sprite sprite;
  SpriteCollision spriteBound;
  double angle;
};

#endif /* end of include guard: TANK_ENTITY_HPP */
