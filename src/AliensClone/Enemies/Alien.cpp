
#include "Alien.h"

Alien::Alien(glm::vec2 pos, int rSize, Player *playerRef, Level *levelRef) : GameObject(pos, rSize), refToPlayer{playerRef}, refToCurrentLevel{levelRef}
{
      Logger::Logg("Alien Constructor");

      animState = AlienAnimState::AAS_Walking;

      imgFilePath = "./assets/sprites/Enemies/Alien/Alien.png";
      gameObjectTag = "Alien";
      velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(ALIENSPEED, 0.0) : glm::vec2(-ALIENSPEED, 0.0);

      isRenderingBloodSplash = false;
      bloodSplashAnimIndex = 0.0;
      hitPos = glm::vec2(0.0, 0.0);
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

      if (animState == AlienAnimState::AAS_Walking)
      {
            walkAnimIndex += deltaTime * 8;
      }
}

void Alien::RenderGameObject(SDL_Renderer *renderer)
{
      CalculateRect();
      switch (animState)
      {
      case AlienAnimState::AAS_Walking:
            RenderAnimation(renderer, alienWalkingSpritesheet, 4, rectSize, &walkAnimIndex, transform.position, false, isFlipped);
            break;
      default:
            break;
      }

      if (isRenderingBloodSplash)
      {
            RenderAnimation(renderer, alienBloodSplashSpritesheet, 4, 64, &bloodSplashAnimIndex, hitPos, true);
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
            hitPos = otherObj->GetPosition();
            isRenderingBloodSplash = true;
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
            refToCurrentLevel->GetAudioManager()->PlaySFX(10);
      }
}
