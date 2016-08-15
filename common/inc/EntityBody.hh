#ifndef ENTITYBODY_HH_
#define ENTITYBODY_HH_

#include "Polygon.hh"
#include "Rectangle.hh"
#include <SFML/Graphics.hpp>
#include <vector>

class EntityBody {
public:
  EntityBody(const std::vector<Polygon> &polygons, const Rectangle &spriteBound,
             const sf::IntRect &textureBound);

  ~EntityBody() = default;
  EntityBody(const EntityBody &other) = default;
  EntityBody(EntityBody &&other) = default;
  EntityBody &operator=(const EntityBody &other) = default;
  EntityBody &operator=(EntityBody &&other) = default;

  void move(const sf::Vector2f &displacement);
  void setPosition(const Position &pos);
  void rotate(double angle);

  const Rectangle &getBound() const;
  const std::vector<Polygon> &getPolygons() const;

private:
  std::vector<Polygon> polygons;
  Rectangle spriteBound;
  sf::IntRect textureBound;
  Position position;
};

#endif /* end of include guard: ENTITYBODY_HH_ */
