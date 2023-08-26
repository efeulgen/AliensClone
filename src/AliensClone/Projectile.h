
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../Engine/GameObject.h"

enum ProjectileType
{
      PT_LaserBlast,
      PT_Flamethrower,
      PT_TrippleShot
};

class Projectile : public GameObject
{
private:
      ProjectileType type;
      double damageAmount;

public:
      Projectile(glm::vec2 pos, glm::vec2 vel, int rSize, ProjectileType t);
      ~Projectile();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void CollisionCallback() override;
};

#endif
