#include "Entities/Player.hh"
#include "Entities/Ball.hh"
#include "Entities/Wall.hh"
#include "Grid.hh"
#include <iostream>

Player::Player(const EntityBody &body, const sf::Sprite &sprite,
               IActionAnalyzer &actionAnalyzer, const EntityBody &ballBody,
               const sf::Sprite &ballSprite)
    : Movable(body, sprite), actionAnalyzer(actionAnalyzer), ballBody(ballBody),
      ballSprite(ballSprite) {}

void Player::spawnBall(Grid &grid) {
  std::shared_ptr<Movable> ball(new Ball(this->ballBody, this->ballSprite));

  Position ballPos = this->position;
  Position gridPos;
  const auto &ballBound = this->ballBody.getBound();
  const auto &spriteBound = this->sprite.getLocalBounds();

  ballPos.x +=
      (this->direction.x * (spriteBound.width / 2 + ballBound.getWidth() / 2));
  ballPos.y += (this->direction.y *
                (spriteBound.height / 2 + ballBound.getHeight() / 2));
  gridPos.x = ballPos.x / spriteBound.width;
  gridPos.y = ballPos.y / spriteBound.height;

  if (gridPos.x < 0 || gridPos.y < 0 || gridPos.x >= grid.getWidth() ||
      gridPos.y >= grid.getHeight()) {
    return;
  }
  ball->setPosition(ballPos);
  ball->setDirection(this->direction);
  grid.addObjectToQueue(ball);
}

void Player::update(Grid &grid, std::chrono::nanoseconds time) {
  const std::vector<Action> &actions = this->actionAnalyzer.getActions();

  for (Action act : actions) {
    switch (act) {
    case Action::Left:
    case Action::Right:
      this->rotate((act == Action::Right ? -Player::alpha : Player::alpha),
                   grid);
      break;
    case Action::Forward:
    case Action::Back:
      this->displace((act == Action::Forward ? 1 : -1), time, grid);
      break;
    case Action::Use:
      this->spawnBall(grid);
      break;
    default:
      break;
    }
  }
}

void Player::impact(std::shared_ptr<Entity> entity,
                    const intersectionResult &inter) {
  entity->getImpacted(*this, inter);
}

void Player::getImpacted(Entity &entity, const intersectionResult &inter) {}
void Player::getImpacted(Ball &ball, const intersectionResult &inter) {
  this->alive = false;
}
