
#include "Alien.h"

Alien::Alien(glm::vec2 pos, int rSize, Player *playerRef) : GameObject(pos, rSize), refToPlayer{playerRef}
{
      Logger::Logg("Alien Constructor");

      imgFilePath = "./assets/sprites/Enemies/Alien/Alien.png";
      gameObjectTag = "Alien";
      velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(ALIENSPEED, 0.0) : glm::vec2(-ALIENSPEED, 0.0);
}

Alien::~Alien()
{
      Logger::Logg("Alien Destructor");
}

void Alien::InitGameObject()
{
}

void Alien::UpdateGameObject(double deltaTime)
{
      if (!refToPlayer)
      {
            return;
      }

      // follow player
      if (abs(refToPlayer->GetTransform().position.x - transform.position.x) > attackRange)
      {
            velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(ALIENSPEED, 0.0) : glm::vec2(-ALIENSPEED, 0.0);
            attackCounter = ATTACK_RATE;
      }
      else
      {
            velocity = glm::vec2(0.0, 0.0);

            if (attackCounter >= ATTACK_RATE)
            {
                  Attack();
                  attackCounter = 0.0;
            }
            else
            {
                  attackCounter += deltaTime;
            }
      }

      // flip
      isFlipped = refToPlayer->GetTransform().position.x > transform.position.x ? true : false;

      transform.position.x += velocity.x * deltaTime;
      transform.position.x += velocity.y * deltaTime;
}

void Alien::CollisionCallback(GameObject *otherObj)
{
      if (otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile")
      {
            GetDamage(static_cast<Projectile *>(otherObj)->GetDamageAmount());
            otherObj->SetCanBeDestroyed(true);
      }
}

void Alien::Attack()
{
      refToPlayer->DamagePlayer(10);
}

void Alien::GetDamage(int damageAmount)
{
      health -= damageAmount;
      if (health <= 0)
      {
            canBeDestroyed = true;
      }
}
