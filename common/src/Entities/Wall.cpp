#include "Entities/Wall.hh"
#include "Entities/Ball.hh"
#include "Entities/Player.hh"

Wall::Wall(const sf::Sprite &sprite) : Entity(sprite) {}

bool Wall::intersect(const Entity &ent) const {
  return false; // not done yet
}
void Wall::draw(sf::RenderTarget &renderTarget) const {
  renderTarget.draw(this->sprite);
  const auto &vertices = spriteBound.getVerticesCalculator().getVertices();
  sf::VertexArray varray(sf::LinesStrip);

  for (const auto &vertice : vertices) {
    // std::cout << vertice.x << " " << vertice.y << "\n";
    varray.append(sf::Vertex(sf::Vector2f(vertice.x, vertice.y),
                             sf::Color(255, 255, 255)));
  }
  renderTarget.draw(varray);
  // auto edges = this->spriteBound.getBound().getEdges();
  //
  // sf::ConvexShape convex(4);
  // for (unsigned int i = 0; i < edges.size(); ++i) {
  //   convex.setPoint(i, sf::Vector2f(edges[i].x, edges[i].y));
  // }
  // convex.setFillColor(sf::Color(0, 0, 0, 0));
  // convex.setOutlineColor(sf::Color(255, 255, 255));
  // convex.setOutlineThickness(1);
  // renderTarget.draw(convex);
}

void Wall::getImpacted(Entity &entity) {}
void Wall::getImpacted(Player &player) {}
void Wall::getImpacted(Ball &ball) {
  ball.bounce();
  ball.computeReflectedDirection(*this);
}