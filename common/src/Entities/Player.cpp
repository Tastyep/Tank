#include "Entities/Player.hh"
#include <iostream>

Player::Player(const sf::Sprite &sprite, IActionAnalyzer &actionAnalyzer)
    : Movable(sprite), actionAnalyzer(actionAnalyzer), angle(270) {
  this->direction.x = std::cos(this->angle * radianConvert);
  this->direction.y = std::sin(this->angle * radianConvert);
}

bool Player::intersect(const Entity &ent) const { return false; }

void Player::rotate(Action act) {
  double radianAngle;
  double rotationSide = (act == Action::Right ? Player::alpha : -Player::alpha);

  this->angle += rotationSide;
  if (this->angle >= 360)
    this->angle = this->angle - 360;
  else if (this->angle < 0)
    this->angle += 360;
  radianAngle = radianConvert * this->angle;
  this->direction.x = std::cos(radianAngle);
  this->direction.y = std::sin(radianAngle);
  this->sprite.rotate(rotationSide);
}

void Player::displace(Action act, std::chrono::nanoseconds time) {
  sf::Vector2f displacement;

  this->acceleration = (act == Action::Forward ? -1 : 1);
  this->velocity = std::min(this->velocity + this->acceleration * time.count(),
                            this->maxVelocity);
  this->velocity = std::max(this->velocity, -this->maxVelocity);
  displacement.x = this->velocity * time.count() * this->direction.x;
  displacement.y = this->velocity * time.count() * this->direction.y;

  this->position.x += displacement.x;
  this->position.y += displacement.y;
  this->sprite.move(displacement.x, displacement.y);
}

void Player::update(Grid &grid, std::chrono::nanoseconds time) {
  const std::vector<Action> &actions = this->actionAnalyzer.getActions();

  for (Action act : actions) {
    switch (act) {
    case Action::Left:
    case Action::Right:
      this->rotate(act);
      break;
    case Action::Forward:
    case Action::Back:
      this->displace(act, time);
      break;
    default:
      break;
    }
  }
}