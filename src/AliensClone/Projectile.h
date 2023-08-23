
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../Engine/GameObject.h"

enum ProjectileType
{
      PT_PlayerProjectile,
      PT_AlienProjectile
};

class Projectile : public GameObject
{
private:
      ProjectileType type;

public:
      Projectile(glm::vec2 pos, glm::vec2 vel, ProjectileType t);
      ~Projectile();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
};

#endif
