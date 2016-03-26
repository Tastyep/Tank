#include "SpriteCollision.hh"
#include <iostream>

void SpriteCollision::computeBounds(const sf::Sprite &sprite) {
  const sf::Texture *texture = sprite.getTexture();
  const sf::IntRect &rect = sprite.getTextureRect();
  sf::Image image = texture->copyToImage();
  sf::Color pixel;

  // init so br is tl & tl is br
  Position tl(rect.left + rect.width, rect.top + rect.height);
  Position br(rect.left, rect.top);
  Position origin = Position(static_cast<float>(rect.width) / 2.f,
                             static_cast<float>(rect.height) / 2.f);
  for (int ty = rect.top; ty < rect.top + rect.height; ++ty) {
    for (int tx = rect.left; tx < rect.left + rect.width; ++tx) {
      pixel = image.getPixel(tx, ty);

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
  tl.x -= (rect.left + origin.x);
  tl.y -= (rect.top + origin.y);
  br.x -= (rect.left + origin.x);
  br.y -= (rect.top + origin.y);
  this->spriteBound = Rectangle(tl, br);
  this->spriteBound.setInternTranslation({tl.x, tl.y});
}

void SpriteCollision::translate(const Position &pos) {
  this->spriteBound.setPosition(pos);
}

void SpriteCollision::rotate(double angle) { this->spriteBound.rotate(angle); }

void SpriteCollision::move(const sf::Vector2f &displacement) {
  this->spriteBound.move(displacement);
}

const Rectangle &SpriteCollision::getBound() const { return this->spriteBound; }

bool SpriteCollision::intersects(const SpriteCollision &spriteCollision) const {
  return this->spriteBound.intersects(spriteCollision.getBound());
}