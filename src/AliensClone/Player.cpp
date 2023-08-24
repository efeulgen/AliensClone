
#include "Player.h"

Player::Player()
{
      Logger::Logg("Player Default Constructor");

      imgFilePath = "./assets/sprites/Player.png";
      velocity = glm::vec2(5.0, 5.0);
}

Player::Player(glm::vec2 pos, glm::vec2 vel) : GameObject(pos, vel)
{
      Logger::Logg("Player Overloaded Constructor");

      imgFilePath = "./assets/sprites/Player.png";
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
      ProcessPlayerInput(deltaTime);
}

void Player::ProcessPlayerInput(double deltaTime)
{
      const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
      if (keyboardState[SDL_SCANCODE_D])
      {
            MoveForward(deltaTime);
      }
      if (keyboardState[SDL_SCANCODE_A])
      {
            MoveBackward(deltaTime);
      }
      if (keyboardState[SDL_SCANCODE_W])
      {
            MoveUp(deltaTime);
      }
      if (keyboardState[SDL_SCANCODE_S])
      {
            MoveDown(deltaTime);
      }
}

void Player::MoveForward(double deltaTime)
{
      transform.position.x += velocity.x * deltaTime;
}

void Player::MoveBackward(double deltaTime)
{
      transform.position.x -= velocity.x * deltaTime;
}

void Player::MoveUp(double deltaTime)
{
      transform.position.y -= velocity.y * deltaTime;
}

void Player::MoveDown(double deltaTime)
{
      transform.position.y += velocity.y * deltaTime;
}

void Player::Fire()
{
}
