
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../Engine/GameObject.h"
#include "../Engine/Level.h"
#include "Projectile.h"

const double FIRE_RATE = 0.25;

class Player : public GameObject
{
private:
      Level *currentLevel = nullptr;

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
