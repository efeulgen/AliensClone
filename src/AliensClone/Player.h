
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../Engine/GameObject.h"
#include "Projectile.h"

class Player : public GameObject
{
private:
      std::vector<Projectile *> projectiles;

public:
      Player();
      Player(glm::vec2 pos, glm::vec2 vel);
      ~Player();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;

      void ProcessPlayerInput(double deltaTime);
      void MoveForward(double deltaTime);
      void MoveBackward(double deltaTime);
      void MoveUp(double deltaTime);
      void MoveDown(double deltaTime);
      void Fire();
};

#endif
