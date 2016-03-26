#ifndef TANK_SRITECOLLISION_HH
#define TANK_SRITECOLLISION_HH

#include "Rectangle.hh"
#include <SFML/Graphics.hpp>

class SpriteCollision {
public:
  SpriteCollision() = default;

  ~SpriteCollision() = default;
  SpriteCollision(const SpriteCollision &other) = default;
  SpriteCollision(SpriteCollision &&other) = default;
  SpriteCollision &operator=(const SpriteCollision &other) = default;
  SpriteCollision &operator=(SpriteCollision &&other) = default;

  void computeBounds(const sf::Sprite &sprite);
  void translate(const Position &pos);
  void move(const sf::Vector2f &displacement);
  void rotate(double angle);
  const Rectangle &getBound() const;
  bool intersects(const SpriteCollision &spriteCollision) const;

private:
  Rectangle spriteBound;
};

#endif /* end of include guard: TANK_SRITECOLLISION_HH */
