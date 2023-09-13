
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
      int damageAmount;

public:
      Projectile(glm::vec2 pos, glm::vec2 vel, int rSize, ProjectileType t, bool flip);
      ~Projectile();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;

      // getters & setters
      int GetDamageAmount() const { return damageAmount; }
};

#endif
