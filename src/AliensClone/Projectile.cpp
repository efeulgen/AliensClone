
#include "Projectile.h"

Projectile::Projectile(glm::vec2 pos, glm::vec2 vel, int rSize, ProjectileType t) : GameObject(pos, vel, rSize), type{t}
{
      // Logger::Logg("Projectile Constructor");

      switch (type)
      {
      case ProjectileType::PT_LaserBlast:
            imgFilePath = "./assets/sprites/Player/Projectiles/PlayerLaserBlasterProjectile.png";
            damageAmount = 5;
            break;
      case ProjectileType::PT_Flamethrower:
            imgFilePath = "./assets/sprites/Player/Projectiles/PlayerFlamethrowerProjectile.png";
            damageAmount = 1;
            break;
      default:
            break;
      }
}

Projectile::~Projectile()
{
      // Logger::Logg("Projectile Destructor");
}

void Projectile::InitGameObject()
{
}

void Projectile::UpdateGameObject(double deltaTime)
{
      transform.position.x += velocity.x * deltaTime;
      transform.position.y += velocity.y * deltaTime;

      if (transform.position.x > 2000.0 || transform.position.x < -100.0)
      {
            canBeDestroyed = true;
      }
}