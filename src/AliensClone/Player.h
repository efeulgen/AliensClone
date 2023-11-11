
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../Engine/GameObject.h"
#include "../Engine/Level.h"
#include "Projectile.h"

const double LASERBLASTER_FIRE_RATE = 0.2;
const double FLAMETHROWER_FIRE_RATE = 0.1;
const double TRIPPLESHOT_FIRE_RATE = 1.5;

const double FACEHUG_DURATION = 2.0;
const double SLOWDOWN_DURATION = 3.0;

enum PlayerWeaponMode
{
      PWM_LaserBlaster,
      PWM_Flamethrower,
      PWM_TrippleShot
};

enum PlayerAnimState
{
      PAS_Idle,
      PAS_Walking
};

class Player : public GameObject
{
private:
      Level *currentLevel = nullptr;
      PlayerWeaponMode weaponMode;
      PlayerAnimState animState;

      bool canFire;
      double fireCounter;
      bool isFiringFlamethrower = false;
      glm::vec2 fireOffset = glm::vec2(0.0, 0.0);
      glm::vec2 firePos = glm::vec2(0.0, 0.0);

      int windowWidth;
      int windowHeight;

      double globalX;

      bool canClimb = false;
      bool isOnGroundLevel = true;
      int upperLevelUpperLimitRatio = 7;
      int upperLevelLowerLimitRatio = 5;
      int groundLevelUpperLimitRatio = 2;

      // muzzle flash anim
      bool isRenderingMuzzleFlash = false;
      double muzzleFlashAnimIndex = 0.0;
      const char *muzzleFlashSpritesheet[3] = {"./assets/sprites/FX/MuzzleFlash/MuzzleFlash_1.png", "./assets/sprites/FX/MuzzleFlash/MuzzleFlash_2.png", "./assets/sprites/FX/MuzzleFlash/MuzzleFlash_3.png"};

      // walk anims
      const char **walkAnimSpritesheet;
      double walkAnimSpeed = 10.0;

      double walkAnimIndex = 0.0;
      const char *laserBlasterWalkSpriteSheet[4] = {"./assets/sprites/Player/Walking/PlayerLaserBlaster_walk_1.png", "./assets/sprites/Player/Walking/PlayerLaserBlaster_walk_2.png", "./assets/sprites/Player/Walking/PlayerLaserBlaster_walk_3.png", "./assets/sprites/Player/Walking/PlayerLaserBlaster_walk_4.png"};
      const char *flamethrowerWalkSpriteSheet[4] = {"./assets/sprites/Player/Walking/PlayerFlamethrower_walk_1.png", "./assets/sprites/Player/Walking/PlayerFlamethrower_walk_2.png", "./assets/sprites/Player/Walking/PlayerFlamethrower_walk_3.png", "./assets/sprites/Player/Walking/PlayerFlamethrower_walk_4.png"};
      const char *trippleShotWalkSpriteSheet[4] = {"./assets/sprites/Player/Walking/PlayerTrippleShot_walk_1.png", "./assets/sprites/Player/Walking/PlayerTrippleShot_walk_2.png", "./assets/sprites/Player/Walking/PlayerTrippleShot_walk_3.png", "./assets/sprites/Player/Walking/PlayerTrippleShot_walk_4.png"};

      const char *laserBlasterInfectedWalkSpriteSheet[4] = {"./assets/sprites/Player/Infected/PlayerLaserBlaster_infected_walk_1.png", "./assets/sprites/Player/Infected/PlayerLaserBlaster_infected_walk_2.png", "./assets/sprites/Player/Infected/PlayerLaserBlaster_infected_walk_3.png", "./assets/sprites/Player/Infected/PlayerLaserBlaster_infected_walk_4.png"};
      const char *flamethrowerInfectedWalkSpriteSheet[4] = {"./assets/sprites/Player/Infected/PlayerFlamethrower_infected_walk_1.png", "./assets/sprites/Player/Infected/PlayerFlamethrower_infected_walk_2.png", "./assets/sprites/Player/Infected/PlayerFlamethrower_infected_walk_3.png", "./assets/sprites/Player/Infected/PlayerFlamethrower_infected_walk_4.png"};
      const char *trippleShotInfectedWalkSpriteSheet[4] = {"./assets/sprites/Player/Infected/PlayerTrippleShot_infected_walk_1.png", "./assets/sprites/Player/Infected/PlayerTrippleShot_infected_walk_2.png", "./assets/sprites/Player/Infected/PlayerTrippleShot_infected_walk_3.png", "./assets/sprites/Player/Infected/PlayerTrippleShot_infected_walk_4.png"};

      // stats
      int health = 100;
      int laserBlasterAmmo = 30;
      int flamethrowerAmmo = 200;
      int trippleShotAmmo = 10;

      bool isFacehugged = false;
      double facehugDurationCounter = 0.0;

      bool isSlowedDown = false;
      double slowDownCounter = 0.0;

public:
      Player(glm::vec2 pos, glm::vec2 vel, int rSize, Level *level, int w, int h);
      ~Player();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
      void CollisionEnterCallback(GameObject *otherObj) override;
      void CollisionExitCallback(GameObject *otherObj) override;
      void CalculateColliderRect() override;

      void ProcessPlayerInput(double deltaTime);
      void MoveForward(double deltaTime);
      void MoveBackward(double deltaTime);
      void MoveUp(double deltaTime);
      void MoveDown(double deltaTime);
      void Fire();
      void Crouch();
      void HealPlayer();
      void IncreaseLaserBlasterAmmo();
      void IncreaseFlamethrowerAmmo();
      void IncreaseTrippleShotAmmo();
      void DamagePlayer(int damageAmount);
      void ActivateIsFacehugged();
      void SlowDownPlayer();

      // getters & setters
      int GetHealth() const { return health; }
      int GetAmmo() const
      {
            switch (weaponMode)
            {
            case PlayerWeaponMode::PWM_LaserBlaster:
                  return laserBlasterAmmo;
            case PlayerWeaponMode::PWM_Flamethrower:
                  return flamethrowerAmmo;
            case PlayerWeaponMode::PWM_TrippleShot:
                  return trippleShotAmmo;
            default:
                  return 0;
            }
      }
};

#endif
