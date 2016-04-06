#ifndef TANK_WALL_HH
#define TANK_WALL_HH

#include "Entity.hh"

class Wall : public Entity {
public:
  Wall(const sf::Sprite &sprite);

  ~Wall() = default;
  Wall(const Wall &other) = default;
  Wall(Wall &&other) = default;
  Wall &operator=(const Wall &other) = default;
  Wall &operator=(Wall &&other) = default;

  bool intersect(const Entity &ent) const;
  void getImpacted(Entity &entity);
  void getImpacted(Ball &entity);
  void getImpacted(Player &player);
  void draw(sf::RenderTarget &renderTarget) const;
};

#endif /* end of include guard: TANK_WALL_HH */
