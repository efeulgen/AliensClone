
#ifndef ALIEN_H
#define ALIEN_H

#include <cstdlib>
#include "../../Engine/GameObject.h"
#include "../Player.h"
#include "../Projectile.h"

const double ALIENSPEED = 400.0;
const double ATTACK_RATE = 1.0;

class Alien : public GameObject
{
private:
      Player *refToPlayer;
      double attackCounter = 0.0;
      double attackRange = 150.0;

      // stats
      int health = 100;

public:
      Alien(glm::vec2 pos, int rSize, Player *playerRef);
      ~Alien();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void CollisionCallback(GameObject *otherObj) override;

      void Attack();
      void GetDamage(int damageAmount);
};

#endif
