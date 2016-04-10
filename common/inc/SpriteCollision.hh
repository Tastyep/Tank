#ifndef TANK_SRITECOLLISION_HH
#define TANK_SRITECOLLISION_HH

#include "Rectangle.hh"
#include "VerticesCalculator.hh"

class SpriteCollision {
public:
  SpriteCollision() = default;
  SpriteCollision(const sf::Sprite &sprite);

  ~SpriteCollision() = default;
  SpriteCollision(const SpriteCollision &other) = default;
  SpriteCollision(SpriteCollision &&other) = default;
  SpriteCollision &operator=(const SpriteCollision &other) = default;
  SpriteCollision &operator=(SpriteCollision &&other) = default;

  void translate(const Position &pos);
  void move(const sf::Vector2f &displacement);
  void rotate(double angle);
  const Rectangle &getBound() const;
  bool intersects(const SpriteCollision &spriteCollision) const;
  VerticesCalculator getVerticesCalculator() const {
    return this->verticesCalculator;
  };

private:
  VerticesCalculator verticesCalculator;
  Rectangle spriteBound;
  Position position;
};

#endif /* end of include guard: TANK_SRITECOLLISION_HH */
