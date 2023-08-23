
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
      ~Player();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;

      void MoveForward();
      void MoveBackward();
      void MoveUp();
      void MoveDown();
      void Fire();
};

#endif
