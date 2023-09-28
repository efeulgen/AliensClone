
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

enum PlayerWeaponMode
{
      PWM_LaserBlaster,
      PWM_Flamethrower,
      PWM_TrippleShot
};

class Player : public GameObject
{
private:
      Level *currentLevel = nullptr;
      PlayerWeaponMode weaponMode;

      bool canFire;
      double fireCounter;
      bool isFiringFlamethrower = false;
      glm::vec2 fireOffset = glm::vec2(0.0, 0.0);
      glm::vec2 firePos = glm::vec2(0.0, 0.0);

      int windowWidth;
      int windowHeight;

      double globalX;

      // muzzle flash anim
      bool isRenderingMuzzleFlash = false;
      double muzzleFlashAnimIndex = 0.0;
      const char *muzzleFlashSpritesheet[3] = {"./assets/sprites/Player/MuzzleFlash/PlayerMuzzleFlash_1.png", "./assets/sprites/Player/MuzzleFlash/PlayerMuzzleFlash_2.png", "./assets/sprites/Player/MuzzleFlash/PlayerMuzzleFlash_3.png"};

      // stats
      int health = 100;
      int laserBlasterAmmo = 30;
      int flamethrowerAmmo = 200;
      int trippleShotAmmo = 10;

      bool isFacehugged = false;
      double facehugDurationCounter = 0.0;

public:
      Player(glm::vec2 pos, glm::vec2 vel, int rSize, Level *level, int w, int h);
      ~Player();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;

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
