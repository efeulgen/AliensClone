
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../Engine/GameObject.h"
#include "../Engine/Level.h"
#include "Projectile.h"

const double LASERBLASTER_FIRE_RATE = 0.25;
const double FLAMETHROWER_FIRE_RATE = 0.05;
const double TRIPPLESHOT_FIRE_RATE = 3.5;

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

      int windowWidth;
      int windowHeight;

public:
      Player(glm::vec2 pos, glm::vec2 vel, int rSize, Level *level, int w, int h);
      ~Player();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;

      void ProcessPlayerInput(double deltaTime);
      void MoveForward(double deltaTime);
      void MoveBackward(double deltaTime);
      void MoveUp(double deltaTime);
      void MoveDown(double deltaTime);
      void Fire();
      void Crouch();
};

#endif
