#include "EntityBody.hh"
#include "Utils.hh"

EntityBody::EntityBody(const std::vector<Polygon> &polygons,
                       const Rectangle &spriteBound,
                       const sf::IntRect &textureBound)
    : polygons(polygons), spriteBound(spriteBound), textureBound(textureBound) {
}

void EntityBody::draw(sf::RenderTarget &renderTarget) const {
  sf::VertexArray varray(sf::LinesStrip);

  for (auto &polygon : this->polygons) {
    const std::vector<Position> &vertices = polygon.getVertices();

    for (const auto &vertice : vertices) {
      varray.append(sf::Vertex(sf::Vector2f(vertice.x, vertice.y),
                               sf::Color(255, 255, 255)));
    }
    varray.append(
        sf::Vertex(sf::Vector2f(vertices.front().x, vertices.front().y),
                   sf::Color(255, 255, 255)));
  }
  // renderTarget.draw(varray);
  this->spriteBound.draw(renderTarget);
}

void EntityBody::move(const sf::Vector2f &displacement) {
  this->position.x += displacement.x;
  this->position.y += displacement.y;
  for (auto &polygon : this->polygons) {
    polygon.move(displacement);
  }
  this->spriteBound.move(displacement);
}

void EntityBody::setPosition(const Position &pos) {
  Position allignedPos = pos;
  this->position = pos;

  allignedPos.x -= this->textureBound.width / 2;
  allignedPos.y -= this->textureBound.height / 2;
  for (auto &polygon : this->polygons) {
    polygon.setPosition(allignedPos);
  }
  this->spriteBound.setPosition(pos);
}

void EntityBody::rotate(double angle) {
  angle *= (Utils::pi / 180.f);
  double cs = std::cos(angle);
  double sn = std::sin(angle);

  for (auto &polygon : this->polygons) {
    polygon.rotate(cs, sn, this->position);
  }
  this->spriteBound.rotate(cs, sn, this->position);
}

const Rectangle &EntityBody::getBound() const { return this->spriteBound; }
const std::vector<Polygon> &EntityBody::getPolygons() const {
  return this->polygons;
}
