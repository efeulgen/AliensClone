
#include "Projectile.h"

Projectile::Projectile(glm::vec2 pos, glm::vec2 vel, ProjectileType t) : type{t}
{
      Logger::Logg("Projectile Constructor");

      transform.position = pos;
      velocity = vel;
      imgFilePath = "./assets/sprites/PlayerProjectile.png";
}

Projectile::~Projectile()
{
      Logger::Logg("Projectile Destructor");
}

void Projectile::InitGameObject()
{
}

void Projectile::UpdateGameObject(double deltaTime)
{
}