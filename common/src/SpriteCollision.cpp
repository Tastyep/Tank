#include "SpriteCollision.hh"
#include <iostream>

SpriteCollision::SpriteCollision(const sf::Sprite &sprite)
    : verticesCalculator(sprite) {
  const sf::Texture *texture = sprite.getTexture();
  const sf::IntRect &rect = sprite.getTextureRect();
  sf::Image image = texture->copyToImage();
  sf::Color pixel;

  // init so br is tl & tl is br
  Position tl(rect.width, rect.height);
  Position br(0, 0);
  Position origin = Position(static_cast<float>(rect.width) / 2.f,
                             static_cast<float>(rect.height) / 2.f);
  for (int ty = 0; ty < rect.height; ++ty) {
    for (int tx = 0; tx < rect.width; ++tx) {
      pixel = image.getPixel(tx + rect.left, ty + rect.top);

      if (pixel.a != 0) { // Not Transparent
        if (ty < tl.y)
          tl.y = ty;
        if (ty > br.y)
          br.y = ty;
        if (tx < tl.x)
          tl.x = tx;
        if (tx > br.x)
          br.x = tx;
      }
    }
  }
  tl.x -= origin.x;
  tl.y -= origin.y;
  br.x -= origin.x;
  br.y -= origin.y;
  this->spriteBound = Rectangle(tl, br);
  this->spriteBound.setInternTranslation({tl.x, tl.y});
  this->verticesCalculator.computeVertices();
}

void SpriteCollision::translate(const Position &pos) {
  this->spriteBound.setPosition(pos);
  this->verticesCalculator.setPosition(pos);
}

void SpriteCollision::rotate(double angle) {
  this->spriteBound.rotate(angle);
  this->verticesCalculator.rotate(angle);
}

void SpriteCollision::move(const sf::Vector2f &displacement) {
  this->spriteBound.move(displacement);
  this->verticesCalculator.move(displacement);
}

const Rectangle &SpriteCollision::getBound() const { return this->spriteBound; }

bool SpriteCollision::intersects(const SpriteCollision &spriteCollision) const {
  if (this->spriteBound.intersects(spriteCollision.getBound())) {
    if (this->verticesCalculator.intersects(
            spriteCollision.getVerticesCalculator().getVertices())) {
      std::cout << "intersects"
                << "\n";
      return true;
    } else
      std::cout << "DONT intersects"
                << "\n";
  }
  return false;
}