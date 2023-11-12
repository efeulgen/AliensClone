
#include "Alien.h"

Alien::Alien(glm::vec2 pos, int rSize, Player *playerRef, Level *levelRef) : GameObject(pos, rSize), refToPlayer{playerRef}, refToCurrentLevel{levelRef}
{
      Logger::Log("Alien Constructor");

      animState = AlienAnimState::AAS_Walking;

      imgFilePath = "./assets/sprites/Enemies/Alien/Alien.png";
      gameObjectTag = "Alien";
      renderPriority = 2;
      velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(ALIENSPEED, 0.0) : glm::vec2(-ALIENSPEED, 0.0);
}

Alien::~Alien()
{
      Logger::Log("Alien Destructor");

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
      // anims
      if (isRenderingBloodSplash)
      {
            bloodSplashAnimIndex += deltaTime * 10;
      }

      if (animState == AlienAnimState::AAS_Walking)
      {
            walkAnimIndex += deltaTime * 8;
      }
      else if (animState == AlienAnimState::AAS_Attacking)
      {
            attackingAnimIndex += deltaTime * 8;
      }
      else if (animState == AlienAnimState::AAS_Death)
      {
            deathAnimIndex += deltaTime * 8;
            return;
      }

      // follow player
      if (abs(refToPlayer->GetTransform().position.x - transform.position.x) > attackRange)
      {
            animState = AlienAnimState::AAS_Walking;
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
}

void Alien::RenderGameObject(SDL_Renderer *renderer)
{
      CalculateRect();
      switch (animState)
      {
      case AlienAnimState::AAS_Walking:
            RenderAnimation(renderer, alienWalkingSpritesheet, 4, rectSize, &walkAnimIndex, transform.position, false, isFlipped);
            break;
      case AlienAnimState::AAS_Attacking:
            RenderAnimation(renderer, alienAttackingSpritesheet, 5, rectSize, &attackingAnimIndex, transform.position, true, isFlipped);
            if (static_cast<int>(attackingAnimIndex) >= 4)
            {
                  attackingAnimIndex = 0.0;
                  animState = AlienAnimState::AAS_Idle;
            }
            break;
      case AlienAnimState::AAS_Idle:
            GameObject::RenderGameObject(renderer);
            break;
      case AlienAnimState::AAS_Death:
            RenderAnimation(renderer, alienDeathSpritesheet, 4, rectSize, &deathAnimIndex, transform.position, true, isFlipped);
            if (static_cast<int>(deathAnimIndex) >= 3)
            {
                  deathAnimIndex = 0.0;
                  canBeDestroyed = true;
            }
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
      animState = AlienAnimState::AAS_Attacking;
      refToPlayer->DamagePlayer(10);
}

void Alien::GetDamage(int damageAmount)
{
      health -= damageAmount;
      if (health <= 0)
      {
            animState = AlienAnimState::AAS_Death;
            refToCurrentLevel->GetAudioManager()->PlaySFX(10);
      }
}
