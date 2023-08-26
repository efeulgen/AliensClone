
#include "Player.h"

Player::Player(glm::vec2 pos, glm::vec2 vel, int rSize, Level *level, int w, int h) : GameObject(pos, vel, rSize), currentLevel{level}, windowWidth{w}, windowHeight{h}
{
      Logger::Logg("Player Constructor");

      imgFilePath = "./assets/sprites/Player/PlayerLaserBlaster.png";
      weaponMode = PlayerWeaponMode::PWM_LaserBlaster;
      fireCounter = LASERBLASTER_FIRE_RATE;
      canFire = true;

      laserBlasterSound = Mix_LoadWAV("./audio/dummy_PlayerLaserBlasterSound.wav");
      flamethrowerSound = Mix_LoadWAV("./audio/dummy_PlayerFlamethrowerSound.wav");
      trippleShotSound = Mix_LoadMUS("./audio/dummy_PlayerTrippleShotSound.mp3");
}

Player::~Player()
{
      Logger::Logg("Player Destructor");

      Mix_FreeChunk(laserBlasterSound);
      Mix_FreeChunk(flamethrowerSound);
      Mix_FreeMusic(trippleShotSound);
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
            fireCounter -= deltaTime;
            if (fireCounter <= 0.0)
            {
                  canFire = true;
                  switch (weaponMode)
                  {
                  case PlayerWeaponMode::PWM_LaserBlaster:
                        fireCounter = LASERBLASTER_FIRE_RATE;
                        break;
                  case PlayerWeaponMode::PWM_Flamethrower:
                        fireCounter = FLAMETHROWER_FIRE_RATE;
                        break;
                  case PlayerWeaponMode::PWM_TrippleShot:
                        fireCounter = TRIPPLESHOT_FIRE_RATE;
                        break;
                  default:
                        break;
                  }
            }
      }

      // shift level background
      if (transform.position.x > windowWidth / 2)
      {
            currentLevel->ShifBackground(600.0, deltaTime);
            transform.position.x = windowWidth / 2;
      }

      // bound checking
      if (transform.position.y < windowHeight / 2)
      {
            transform.position.y = windowHeight / 2;
      }
      if (transform.position.y > windowHeight - rectSize)
      {
            transform.position.y = windowHeight - rectSize;
      }
}

void Player::CollisionCallback()
{
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
            if (weaponMode == PlayerWeaponMode::PWM_Flamethrower && !isFiringFlamethrower)
            {
                  isFiringFlamethrower = true;
                  flamethrowerChannel = Mix_PlayChannel(-1, flamethrowerSound, 0);
            }
      }
      if (!keyboardState[SDL_SCANCODE_RETURN])
      {
            isFiringFlamethrower = false;
            if (weaponMode == PlayerWeaponMode::PWM_Flamethrower)
            {
                  Mix_HaltChannel(flamethrowerChannel);
            }
      }
      if (keyboardState[SDL_SCANCODE_1])
      {
            imgFilePath = "./assets/sprites/Player/PlayerLaserBlaster.png";
            weaponMode = PlayerWeaponMode::PWM_LaserBlaster;
            fireCounter = LASERBLASTER_FIRE_RATE;
      }
      if (keyboardState[SDL_SCANCODE_2])
      {
            imgFilePath = "./assets/sprites/Player/PlayerFlamethrower.png";
            weaponMode = PlayerWeaponMode::PWM_Flamethrower;
            fireCounter = FLAMETHROWER_FIRE_RATE;
      }
      if (keyboardState[SDL_SCANCODE_3])
      {
            // imgFilePath = "./assets/sprites/Player/PlayerTrippleShot.png";
            weaponMode = PlayerWeaponMode::PWM_TrippleShot;
            fireCounter = TRIPPLESHOT_FIRE_RATE;
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
      double speed;
      glm::vec2 vel;
      glm::vec2 offset;
      switch (weaponMode)
      {
      case PlayerWeaponMode::PWM_LaserBlaster:
            speed = 2000.0;
            vel = isFlipped ? glm::vec2(-speed, 0.0) : glm::vec2(speed, 0.0);
            offset = isFlipped ? glm::vec2(-8.0, static_cast<double>(rectSize) / 2 - 12.0) : glm::vec2(static_cast<double>(rectSize) + 3.0, static_cast<double>(rectSize) / 2 - 12.0);
            currentLevel->InstantiateGameObject(new Projectile(glm::vec2(transform.position.x, transform.position.y) + offset, vel, 32, ProjectileType::PT_LaserBlast));
            laserBlasterChannel = Mix_PlayChannel(-1, laserBlasterSound, 0);
            break;
      case PlayerWeaponMode::PWM_Flamethrower:
            speed = 1500.0;
            vel = isFlipped ? glm::vec2(-speed, 0.0) : glm::vec2(speed, 0.0);
            offset = isFlipped ? glm::vec2(-8.0, static_cast<double>(rectSize) / 2 - 12.0) : glm::vec2(static_cast<double>(rectSize) + 3.0, static_cast<double>(rectSize) / 2 - 12.0);
            currentLevel->InstantiateGameObject(new Projectile(glm::vec2(transform.position.x, transform.position.y) + offset, vel, 32, ProjectileType::PT_Flamethrower));
            break;
      case PlayerWeaponMode::PWM_TrippleShot:
            // tripple shot code
            break;

      default:
            break;
      }
}

void Player::Crouch()
{
      std::cout << "Player crouches" << std::endl;
}

void Player::HealPlayer()
{
      health += 10;
      if (health > 100)
      {
            health = 100;
      }
}

void Player::IncreaseLaserBlasterAmmo()
{
      std::cout << "Increase LaserBlaster Ammo" << std::endl;
      laserBlasterAmmo += 30;
}

void Player::IncreaseFlamethrowerAmmo()
{
      flamethrowerAmmo += 50;
}

void Player::IncreaseTrippleShotAmmo()
{
      trippleShotAmmo += 2;
}
