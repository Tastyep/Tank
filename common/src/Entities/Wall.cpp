#include "Entities/Wall.hh"
#include "Entities/Ball.hh"
#include "Entities/Player.hh"

Wall::Wall(const sf::Sprite &sprite) : Entity(sprite) {}

intersectionResult Wall::intersects(const Entity &ent) const {
  return intersectionResult(false); // not done yet
}
void Wall::draw(sf::RenderTarget &renderTarget) const {
  renderTarget.draw(this->sprite);
  const auto &polygons = spriteBound.getVerticesCalculator().getPolygons();
  sf::VertexArray varray(sf::LinesStrip);

  for (auto &polygon : polygons) {
    std::vector<Position> vertices = polygon.getVertices();

    vertices.push_back(vertices.front());
    for (const auto &vertice : vertices) {
      varray.append(sf::Vertex(sf::Vector2f(vertice.x, vertice.y),
                               sf::Color(255, 255, 255)));
    }
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

void Wall::getImpacted(Entity &entity, const intersectionResult &inter) {}
void Wall::getImpacted(Player &player, const intersectionResult &inter) {}
void Wall::getImpacted(Ball &ball, const intersectionResult &inter) {
  ball.bounce();
  ball.computeReflectedDirection(*this, inter);
}