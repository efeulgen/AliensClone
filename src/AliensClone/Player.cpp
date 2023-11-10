
#include "Player.h"

Player::Player(glm::vec2 pos, glm::vec2 vel, int rSize, Level *level, int w, int h) : GameObject(pos, vel, rSize), currentLevel{level}, windowWidth{w}, windowHeight{h}
{
      Logger::Log("Player Constructor");

      imgFilePath = "./assets/sprites/Player/PlayerLaserBlaster.png";
      gameObjectTag = "Player";

      weaponMode = PlayerWeaponMode::PWM_LaserBlaster;
      animState = PlayerAnimState::PAS_Idle;
      walkAnimSpritesheet = laserBlasterWalkSpriteSheet;
      fireCounter = LASERBLASTER_FIRE_RATE;
      canFire = true;
      globalX = pos.x;
}

Player::~Player()
{
      Logger::Log("Player Destructor");

      currentLevel = nullptr;
}

void Player::InitGameObject()
{
}

void Player::UpdateGameObject(double deltaTime)
{
      // anims
      if (isRenderingMuzzleFlash)
      {
            muzzleFlashAnimIndex += deltaTime * 10;
      }

      if (animState == PlayerAnimState::PAS_Walking)
      {
            walkAnimIndex += deltaTime * walkAnimSpeed;
      }

      // facehug duration
      if (isFacehugged)
      {
            facehugDurationCounter += deltaTime;
            if (facehugDurationCounter >= FACEHUG_DURATION)
            {
                  isFacehugged = false;
                  facehugDurationCounter = 0.0;
                  switch (weaponMode)
                  {
                  case PlayerWeaponMode::PWM_LaserBlaster:
                        imgFilePath = "./assets/sprites/Player/PlayerLaserBlaster.png";
                        break;
                  case PlayerWeaponMode::PWM_Flamethrower:
                        imgFilePath = "./assets/sprites/Player/PlayerFlamethrower.png";
                        break;
                  case PlayerWeaponMode::PWM_TrippleShot:
                        imgFilePath = "./assets/sprites/Player/PlayerTrippleShot.png";
                        break;
                  default:
                        break;
                  }
            }
            else
            {
                  return;
            }
      }

      // slow down duration
      if (isSlowedDown)
      {
            slowDownCounter += deltaTime;
            if (slowDownCounter >= SLOWDOWN_DURATION)
            {
                  slowDownCounter = 0.0;
                  velocity.x *= 2;
                  velocity.y *= 2;
                  walkAnimSpeed *= 2;
                  isSlowedDown = false;
                  switch (weaponMode)
                  {
                  case PlayerWeaponMode::PWM_LaserBlaster:
                        imgFilePath = "./assets/sprites/Player/PlayerLaserBlaster.png";
                        walkAnimSpritesheet = laserBlasterWalkSpriteSheet;
                        break;
                  case PlayerWeaponMode::PWM_Flamethrower:
                        imgFilePath = "./assets/sprites/Player/PlayerFlamethrower.png";
                        walkAnimSpritesheet = flamethrowerWalkSpriteSheet;
                        break;
                  case PlayerWeaponMode::PWM_TrippleShot:
                        imgFilePath = "./assets/sprites/Player/PlayerTrippleShot.png";
                        walkAnimSpritesheet = trippleShotWalkSpriteSheet;
                        break;
                  default:
                        break;
                  }
            }
      }

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
      // bound checking
      isOnGroundLevel = transform.position.y <= (windowHeight / groundLevelUpperLimitRatio) - 100 ? false : true;
      if (isOnGroundLevel && !canClimb)
      {
            if (transform.position.y < windowHeight / groundLevelUpperLimitRatio)
            {
                  transform.position.y = windowHeight / groundLevelUpperLimitRatio;
            }
            if (transform.position.y > windowHeight - rectSize)
            {
                  transform.position.y = windowHeight - rectSize;
            }
      }
      else if (!isOnGroundLevel && !canClimb)
      {
            if (transform.position.y < windowHeight / upperLevelUpperLimitRatio)
            {
                  transform.position.y = windowHeight / upperLevelUpperLimitRatio;
            }
            if (transform.position.y > windowHeight / upperLevelLowerLimitRatio)
            {
                  transform.position.y = windowHeight / upperLevelLowerLimitRatio;
            }
      }

      if (transform.position.x < 0)
      {
            transform.position.x = 0;
            globalX = 0;
      }

      // finish level
      if (globalX > currentLevel->GetLevelLength() + windowWidth / 2)
      {
            currentLevel->SetIsLevelComplete(true);
      }
}

void Player::RenderGameObject(SDL_Renderer *renderer)
{
      switch (animState)
      {
      case PlayerAnimState::PAS_Idle:
            GameObject::RenderGameObject(renderer);
            break;
      case PlayerAnimState::PAS_Walking:
            CalculateRect();
            RenderAnimation(renderer, walkAnimSpritesheet, 4, rectSize, &walkAnimIndex, transform.position, false, isFlipped);
            break;
      default:
            break;
      }

      if (isRenderingMuzzleFlash)
      {
            glm::vec2 offset = isFlipped ? glm::vec2(-10.0, -15.0) : glm::vec2(-32.0, -15.0);
            RenderAnimation(renderer, muzzleFlashSpritesheet, 3, 64, &muzzleFlashAnimIndex, firePos + offset, true);
            if (static_cast<int>(muzzleFlashAnimIndex) >= 2)
            {
                  isRenderingMuzzleFlash = false;
                  muzzleFlashAnimIndex = 0.0;
            }
      }
}

void Player::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if (otherObj->GetGameObjectTag() == "AmmoPickup")
      {
            currentLevel->GetAudioManager()->PlaySFX(2);
      }

      if (otherObj->GetGameObjectTag() == "HealthPickup")
      {
            if (health == 100)
                  return;
            currentLevel->GetAudioManager()->PlaySFX(11);
      }

      if (otherObj->GetGameObjectTag() == "Ladder")
      {
            canClimb = true;
      }
}

void Player::CollisionExitCallback(GameObject *otherObj)
{
      if (otherObj->GetGameObjectTag() == "Ladder")
      {
            canClimb = false;
      }
}

void Player::CalculateColliderRect()
{
      double xPos = isFlipped ? transform.position.x + (rectSize / 2) : transform.position.x;
      colliderRect = {static_cast<int>(xPos),
                      static_cast<int>(transform.position.y),
                      static_cast<int>((rectSize / 2) * transform.scale.x),
                      static_cast<int>(rectSize * transform.scale.y)};
}

void Player::ProcessPlayerInput(double deltaTime)
{
      const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
      if (keyboardState[SDL_SCANCODE_D])
      {
            MoveForward(deltaTime);
            animState = PlayerAnimState::PAS_Walking;
      }
      if (keyboardState[SDL_SCANCODE_A])
      {
            MoveBackward(deltaTime);
            animState = PlayerAnimState::PAS_Walking;
      }
      if (keyboardState[SDL_SCANCODE_W])
      {
            MoveUp(deltaTime);
            animState = PlayerAnimState::PAS_Walking;
      }
      if (keyboardState[SDL_SCANCODE_S])
      {
            MoveDown(deltaTime);
            animState = PlayerAnimState::PAS_Walking;
      }
      if (!keyboardState[SDL_SCANCODE_D] && !keyboardState[SDL_SCANCODE_A] && !keyboardState[SDL_SCANCODE_W] && !keyboardState[SDL_SCANCODE_S])
      {
            animState = PlayerAnimState::PAS_Idle;
      }
      if (keyboardState[SDL_SCANCODE_RETURN] && canFire)
      {
            Fire();
            canFire = false;
            if (weaponMode == PlayerWeaponMode::PWM_Flamethrower && !isFiringFlamethrower)
            {
                  if (flamethrowerAmmo > 0)
                  {
                        currentLevel->GetAudioManager()->PlaySFX(1);
                        isFiringFlamethrower = true;
                  }
                  else
                  {
                        currentLevel->GetAudioManager()->PlaySFX(3);
                  }
            }
      }
      if (!keyboardState[SDL_SCANCODE_RETURN])
      {
            isFiringFlamethrower = false;
            if (weaponMode == PlayerWeaponMode::PWM_Flamethrower)
            {
                  currentLevel->GetAudioManager()->StopSFX(1);
            }
      }
      if (keyboardState[SDL_SCANCODE_1])
      {
            imgFilePath = isSlowedDown ? "./assets/sprites/Player/Infected/PlayerLaserBlaster_infected_walk_1.png" : "./assets/sprites/Player/PlayerLaserBlaster.png";
            weaponMode = PlayerWeaponMode::PWM_LaserBlaster;
            walkAnimSpritesheet = isSlowedDown ? laserBlasterInfectedWalkSpriteSheet : laserBlasterWalkSpriteSheet;
            fireCounter = LASERBLASTER_FIRE_RATE;
      }
      if (keyboardState[SDL_SCANCODE_2])
      {
            imgFilePath = isSlowedDown ? "./assets/sprites/Player/Infected/PlayerFlamethrower_infected_walk_1.png" : "./assets/sprites/Player/PlayerFlamethrower.png";
            weaponMode = PlayerWeaponMode::PWM_Flamethrower;
            walkAnimSpritesheet = isSlowedDown ? flamethrowerInfectedWalkSpriteSheet : flamethrowerWalkSpriteSheet;
            fireCounter = FLAMETHROWER_FIRE_RATE;
      }
      if (keyboardState[SDL_SCANCODE_3])
      {
            imgFilePath = isSlowedDown ? "./assets/sprites/Player/Infected/PlayerTrippleShot_infected_walk_1.png" : "./assets/sprites/Player/PlayerTrippleShot.png";
            weaponMode = PlayerWeaponMode::PWM_TrippleShot;
            walkAnimSpritesheet = isSlowedDown ? trippleShotInfectedWalkSpriteSheet : trippleShotWalkSpriteSheet;
            fireCounter = TRIPPLESHOT_FIRE_RATE;
      }
}

void Player::MoveForward(double deltaTime)
{
      transform.position.x += velocity.x * deltaTime;
      globalX += velocity.x * deltaTime;
      isFlipped = false;

      if (globalX > ((windowWidth / 2) - (rectSize / 2)) && globalX < currentLevel->GetLevelLength())
      {
            currentLevel->ShifBackground(velocity.x, deltaTime);
            transform.position.x = ((windowWidth / 2) - (rectSize / 2));
      }
}

void Player::MoveBackward(double deltaTime)
{
      transform.position.x -= velocity.x * deltaTime;
      globalX -= velocity.x * deltaTime;
      isFlipped = true;

      if (globalX > ((windowWidth / 2) - (rectSize / 2)) && globalX < currentLevel->GetLevelLength())
      {
            currentLevel->ShifBackground(-velocity.x, deltaTime);
            transform.position.x = ((windowWidth / 2) - (rectSize / 2));
      }
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
      switch (weaponMode)
      {
      case PlayerWeaponMode::PWM_LaserBlaster:
            if (laserBlasterAmmo <= 0)
            {
                  currentLevel->GetAudioManager()->PlaySFX(3);
                  return;
            }
            isRenderingMuzzleFlash = true;
            speed = 2000.0;
            vel = isFlipped ? glm::vec2(-speed, 0.0) : glm::vec2(speed, 0.0);
            fireOffset = isFlipped ? glm::vec2(-15.0, static_cast<double>(rectSize) / 2 - 11.5) : glm::vec2(static_cast<double>(rectSize), static_cast<double>(rectSize) / 2 - 11.5);
            firePos = transform.position + fireOffset;
            currentLevel->InstantiateGameObject(new Projectile(firePos, vel, 32, ProjectileType::PT_LaserBlast, isFlipped));
            currentLevel->GetAudioManager()->PlaySFX(0);
            laserBlasterAmmo--;
            break;
      case PlayerWeaponMode::PWM_Flamethrower:
            if (flamethrowerAmmo <= 0)
            {
                  return;
            }
            speed = 1500.0;
            vel = isFlipped ? glm::vec2(-speed, 0.0) : glm::vec2(speed, 0.0);
            fireOffset = isFlipped ? glm::vec2(10.0, static_cast<double>(rectSize) / 2 - 12.5) : glm::vec2(static_cast<double>(rectSize) - 40.0, static_cast<double>(rectSize) / 2 - 12.5);
            firePos = transform.position + fireOffset;
            currentLevel->InstantiateGameObject(new Projectile(firePos, vel, 32, ProjectileType::PT_Flamethrower, isFlipped));
            flamethrowerAmmo--;
            break;
      case PlayerWeaponMode::PWM_TrippleShot:
            if (trippleShotAmmo <= 0)
            {
                  currentLevel->GetAudioManager()->PlaySFX(3);
                  return;
            }
            speed = 1500.0;
            fireOffset = isFlipped ? glm::vec2(-8.0, static_cast<double>(rectSize) / 2 - 12.0) : glm::vec2(static_cast<double>(rectSize) + 3.0, static_cast<double>(rectSize) / 2 - 12.0);
            firePos = transform.position + fireOffset;
            // mid
            vel = isFlipped ? glm::vec2(-speed, 0.0) : glm::vec2(speed, 0.0);
            currentLevel->InstantiateGameObject(new Projectile(firePos, vel, 64, ProjectileType::PT_TrippleShot, isFlipped));
            // top
            vel = isFlipped ? glm::vec2(-speed, -200.0) : glm::vec2(speed, -200.0);
            currentLevel->InstantiateGameObject(new Projectile(firePos, vel, 64, ProjectileType::PT_TrippleShot, isFlipped));
            // bottom
            vel = isFlipped ? glm::vec2(-speed, 200.0) : glm::vec2(speed, 200.0);
            currentLevel->InstantiateGameObject(new Projectile(firePos, vel, 64, ProjectileType::PT_TrippleShot, isFlipped));

            trippleShotAmmo--;
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

void Player::DamagePlayer(int damageAmount)
{
      health -= damageAmount;
      currentLevel->GetAudioManager()->PlaySFX(5);
      if (health <= 0)
      {
            currentLevel->GetRefToGameManager()->SetIsPlayerDead(true);
            currentLevel->GetRefToGameManager()->SetIsGameOver(true);
            canBeDestroyed = true;
      }
}

void Player::ActivateIsFacehugged()
{
      switch (weaponMode)
      {
      case PlayerWeaponMode::PWM_LaserBlaster:
            imgFilePath = "./assets/sprites/Player/PlayerLaserBlaster_facehugged.png";
            break;
      case PlayerWeaponMode::PWM_Flamethrower:
            imgFilePath = "./assets/sprites/Player/PlayerFlamethrower_facehugged.png";
            break;
      case PlayerWeaponMode::PWM_TrippleShot:
            imgFilePath = "./assets/sprites/Player/PlayerTrippleShot_facehugged.png";
            break;
      default:
            break;
      }
      animState = PlayerAnimState::PAS_Idle;
      isFacehugged = true;
      DamagePlayer(5);
}

void Player::SlowDownPlayer()
{
      if (!isSlowedDown)
      {
            switch (weaponMode)
            {
            case PlayerWeaponMode::PWM_LaserBlaster:
                  imgFilePath = "./assets/sprites/Player/Infected/PlayerLaserBlaster_infected_walk_1.png";
                  walkAnimSpritesheet = laserBlasterInfectedWalkSpriteSheet;
                  break;
            case PlayerWeaponMode::PWM_Flamethrower:
                  imgFilePath = "./assets/sprites/Player/Infected/PlayerFlamethrower_infected_walk_1.png";
                  walkAnimSpritesheet = flamethrowerInfectedWalkSpriteSheet;
                  break;
            case PlayerWeaponMode::PWM_TrippleShot:
                  imgFilePath = "./assets/sprites/Player/Infected/PlayerTrippleShot_infected_walk_1.png";
                  walkAnimSpritesheet = trippleShotInfectedWalkSpriteSheet;
                  break;
            default:
                  break;
            }

            isSlowedDown = true;
            velocity.x /= 2;
            velocity.y /= 2;
            walkAnimSpeed /= 2;
      }
}
