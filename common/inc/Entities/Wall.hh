#ifndef TANK_WALL_HH
#define TANK_WALL_HH

#include "Entity.hh"

class Wall : public Entity {
public:
  Wall(const EntityBody &body, const sf::Sprite &sprite);

  ~Wall() = default;
  Wall(const Wall &other) = default;
  Wall(Wall &&other) = default;
  Wall &operator=(const Wall &other) = default;
  Wall &operator=(Wall &&other) = default;

  intersectionResult intersects(const Entity &ent) const;
  void getImpacted(Entity &entity, const intersectionResult &inter);
  void getImpacted(Ball &entity, const intersectionResult &inter);
  void getImpacted(Player &player, const intersectionResult &inter);
  void draw(sf::RenderTarget &renderTarget) const;
};

#endif /* end of include guard: TANK_WALL_HH */
