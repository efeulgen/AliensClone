
#include "Possessed.h"

Possessed::Possessed(glm::vec2 pos, int rSize, Player *p, Level *l) : GameObject(pos, rSize), refToPlayer{p}, refToLevel{l}
{
      Logger::Log("Possessed Constructor");

      imgFilePath = "./assets/sprites/Enemies/Possessed/Possessed_idle.png";
      gameObjectTag = "Possessed";
      velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(possessedSpeed, 0.0) : glm::vec2(-possessedSpeed, 0.0);
      animState = PossessedAnimState::POSAS_Walking;
}

Possessed::~Possessed()
{
      Logger::Log("Possessed Destructor");
}

void Possessed::InitGameObject()
{
}

void Possessed::UpdateGameObject(double deltaTime)
{
      if (refToLevel->GetRefToGameManager()->GetIsGameOver())
            return;

      // anims
      possessedWalkAnimIndex += deltaTime * 2;
      if (isDead)
      {
            possessedDeathAnimIndex += deltaTime * 5;
            return;
      }
      if (animState == PossessedAnimState::POSAS_Attack)
      {
            possessedAttackAnimIndex += deltaTime * 5;
      }

      // follow player
      if (abs(refToPlayer->GetTransform().position.x - transform.position.x) > attackRange)
      {
            velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(possessedSpeed, 0.0) : glm::vec2(-possessedSpeed, 0.0);
            attackCounter = attackRate;
            animState = PossessedAnimState::POSAS_Walking;
      }
      else
      {
            velocity = glm::vec2(0.0, 0.0);

            if (attackCounter >= attackRate)
            {
                  Attack();
                  attackCounter = 0.0;
                  animState = PossessedAnimState::POSAS_Attack;
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

void Possessed::RenderGameObject(SDL_Renderer *renderer)
{
      if (!isDead)
      {
            CalculateRect();
            switch (animState)
            {
            case PossessedAnimState::POSAS_Walking:
                  RenderAnimation(renderer, possessedWalkSpriteSheet, 4, rectSize, &possessedWalkAnimIndex, transform.position, false, isFlipped);
                  break;
            case PossessedAnimState::POSAS_Attack:
                  RenderAnimation(renderer, possessedAttackSpriteSheet, 4, rectSize, &possessedAttackAnimIndex, transform.position, true, isFlipped);
                  if (static_cast<int>(possessedAttackAnimIndex) >= 3)
                  {
                        possessedAttackAnimIndex = 0.0;
                        animState = PossessedAnimState::POSAS_Idle;
                  }
                  break;
            case PossessedAnimState::POSAS_Idle:
                  GameObject::RenderGameObject(renderer);
                  break;
            default:
                  break;
            }
      }
      else
      {
            RenderAnimation(renderer, possessedDeathSpriteSheet, 6, rectSize, &possessedDeathAnimIndex, transform.position, true, isFlipped);
            if (static_cast<int>(possessedDeathAnimIndex) >= 5)
            {
                  possessedDeathAnimIndex = 0.0;
                  canBeDestroyed = true;
            }
      }
}

void Possessed::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if (otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile")
      {
            GetDamage(static_cast<Projectile *>(otherObj)->GetDamageAmount());
            refToLevel->GetAudioManager()->PlaySFX(12);
            otherObj->SetCanBeDestroyed(true);
      }
}

void Possessed::Attack()
{
      if (isDead)
            return;
      refToPlayer->DamagePlayer(30);
}

void Possessed::GetDamage(int amount)
{
      health -= amount;
      if (health <= 0)
      {
            refToLevel->GetAudioManager()->PlaySFX(10);
            isDead = true;
      }
}
