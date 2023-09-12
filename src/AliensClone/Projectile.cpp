
#include "Projectile.h"

Projectile::Projectile(glm::vec2 pos, glm::vec2 vel, int rSize, ProjectileType t, bool flip) : GameObject(pos, vel, rSize), type{t}
{
      // Logger::Logg("Projectile Constructor");

      isFlipped = flip;

      switch (type)
      {
      case ProjectileType::PT_LaserBlast:
            imgFilePath = "./assets/sprites/Player/Projectiles/PlayerLaserBlasterProjectile.png";
            damageAmount = 35;
            gameObjectTag = "LaserBlasterProjectile";
            break;
      case ProjectileType::PT_Flamethrower:
            imgFilePath = "./assets/sprites/Player/Projectiles/PlayerFlamethrowerProjectile.png";
            damageAmount = 10;
            gameObjectTag = "FlamethrowerProjectile";
            break;
      case ProjectileType::PT_TrippleShot:
            imgFilePath = "./assets/sprites/Player/Projectiles/PlayerTrippleShotProjectile.png";
            damageAmount = 50;
            gameObjectTag = "TrippleShotProjectile";
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

      if (type == ProjectileType::PT_Flamethrower)
      {
            transform.scale.x += deltaTime * 10;
            transform.scale.y += deltaTime * 10;
            transform.position.y -= deltaTime * 200;
      }

      if (transform.position.x > 2000.0 || transform.position.x < -100.0)
      {
            canBeDestroyed = true;
      }
}

void Projectile::CollisionCallback(GameObject *otherObj)
{
}
