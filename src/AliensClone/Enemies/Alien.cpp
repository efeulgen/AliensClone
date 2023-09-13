
#include "Alien.h"

Alien::Alien(glm::vec2 pos, int rSize, Player *playerRef, Level *levelRef) : GameObject(pos, rSize), refToPlayer{playerRef}, refToCurrentLevel{levelRef}
{
      Logger::Logg("Alien Constructor");

      imgFilePath = "./assets/sprites/Enemies/Alien/Alien.png";
      gameObjectTag = "Alien";
      velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(ALIENSPEED, 0.0) : glm::vec2(-ALIENSPEED, 0.0);
}

Alien::~Alien()
{
      Logger::Logg("Alien Destructor");

      refToPlayer = nullptr;
      refToCurrentLevel = nullptr;
}

void Alien::InitGameObject()
{
}

void Alien::UpdateGameObject(double deltaTime)
{
      if (refToCurrentLevel->GetRefToGameManager()->GetIsGameOver())
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
      transform.position.y += velocity.y * deltaTime;

      // anims
      if (isRenderingBloodSplash)
      {
            bloodSplashAnimIndex += deltaTime * 10;
      }
}

void Alien::RenderGameObject(SDL_Renderer *renderer)
{
      GameObject::RenderGameObject(renderer);

      if (isRenderingBloodSplash)
      {
            RenderAnimation(renderer, alienBloodSplashSpritesheet, 64, bloodSplashAnimIndex, hitPos); // transform.position for debugging; get collision pos later
            if (static_cast<int>(bloodSplashAnimIndex) >= 3)
            {
                  isRenderingBloodSplash = false;
                  bloodSplashAnimIndex = 0.0;
            }
      }
}

void Alien::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if (otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile")
      {
            isRenderingBloodSplash = true;
            // hitPos = glm::vec2(hitRect->x, hitRect->y);
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
