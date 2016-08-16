#include "Entities/Wall.hh"
#include "Entities/Ball.hh"
#include "Entities/Player.hh"

Wall::Wall(const EntityBody &body, const sf::Sprite &sprite)
    : Entity(body, sprite) {}

intersectionResult Wall::intersects(const Entity &ent) const {
  return intersectionResult(false); // not done yet
}
void Wall::draw(sf::RenderTarget &renderTarget) const {
  renderTarget.draw(this->sprite);
  this->body.draw(renderTarget);
}

void Wall::getImpacted(Entity &entity, const intersectionResult &inter) {}
void Wall::getImpacted(Player &player, const intersectionResult &inter) {}
void Wall::getImpacted(Ball &ball, const intersectionResult &inter) {
  ball.bounce();
  ball.computeReflectedDirection(*this, inter);
}
