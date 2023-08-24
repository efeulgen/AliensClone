
#include "Player.h"

Player::Player(glm::vec2 pos, glm::vec2 vel, int rSize, Level *level) : GameObject(pos, vel, rSize)
{
      Logger::Logg("Player Constructor");

      imgFilePath = "./assets/sprites/Player.png";
      currentLevel = level;

      canFire = true;
      fireCounter = 0.0;
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

      // fire
      if (!canFire)
      {
            fireCounter += deltaTime;
            if (fireCounter > FIRE_RATE)
            {
                  canFire = true;
                  fireCounter = 0.0;
            }
      }
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
      if (keyboardState[SDL_SCANCODE_RETURN] && canFire)
      {
            Fire();
            canFire = false;
      }
}

void Player::MoveForward(double deltaTime)
{
      transform.position.x += velocity.x * deltaTime;
      isFlipped = false;
}

void Player::MoveBackward(double deltaTime)
{
      transform.position.x -= velocity.x * deltaTime;
      isFlipped = true;
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
      double speed = 2000.0;
      glm::vec2 vel = isFlipped ? glm::vec2(-speed, 0.0) : glm::vec2(speed, 0.0);
      glm::vec2 offset = isFlipped ? glm::vec2(-8.0, static_cast<double>(rectSize) / 2 - 12.0) : glm::vec2(static_cast<double>(rectSize) + 3.0, static_cast<double>(rectSize) / 2 - 12.0);
      currentLevel->InstantiateGameObject(new Projectile(glm::vec2(transform.position.x, transform.position.y) + offset, vel, 32, ProjectileType::PT_PlayerProjectile));
}

void Player::Crouch()
{
      std::cout << "Player crouches" << std::endl;
}
