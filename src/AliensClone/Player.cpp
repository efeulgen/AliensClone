
#include "Player.h"

Player::Player()
{
      Logger::Logg("Player Constructor");

      imgFilePath = "./assets/sprites/Player.png";
      velocity = glm::vec2(5.0, 5.0);
}

Player::~Player()
{
      Logger::Logg("Player Destructor");
}

void Player::InitGameObject()
{
}

void Player::UpdateGameObject(double deltaTime)
{
}

void Player::MoveForward()
{
      transform.position.x += velocity.x;
}

void Player::MoveBackward()
{
      transform.position.x -= velocity.x;
}

void Player::MoveUp()
{
      transform.position.y -= velocity.y;
}

void Player::MoveDown()
{
      transform.position.y += velocity.y;
}

void Player::Fire()
{
}
