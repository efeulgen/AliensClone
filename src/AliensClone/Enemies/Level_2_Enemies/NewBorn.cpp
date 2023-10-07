
#include "NewBorn.h"

NewBorn::NewBorn(glm::vec2 pos, int rSize, Player *p, Level *l) : GameObject(pos, rSize), refToPlayer{p}, refToLevel{l}
{
      Logger::Logg("NewBorn Constructor");

      imgFilePath = "./assets/sprites/Enemies/NewBorn/NewBorn_1.png";
      gameObjectTag = "NewBorn";
      velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(newBornSpeed, 0.0) : glm::vec2(-newBornSpeed, 0.0);
      animState = NewBornAnimState::NBAS_Crawling;
}

NewBorn::~NewBorn()
{
      Logger::Logg("NewBorn Destructor");
}

void NewBorn::InitGameObject()
{
}

void NewBorn::UpdateGameObject(double deltaTime)
{
      if (refToLevel->GetRefToGameManager()->GetIsGameOver())
            return;

      // anims
      newBornAnimIndex += deltaTime * 8;
      if (isDead)
      {
            newBornDeathAnimIndex += deltaTime * 8;
            return;
      }

      if (animState == NewBornAnimState::NBAS_Attacking)
      {
            newBornAttackAnimIndex += deltaTime * 10;
      }

      // follow player
      if (abs(refToPlayer->GetTransform().position.x - transform.position.x) > attackRange)
      {
            velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(newBornSpeed, 0.0) : glm::vec2(-newBornSpeed, 0.0);
            attackCounter = attackRate;
            animState = NewBornAnimState::NBAS_Crawling;
      }
      else
      {
            velocity = glm::vec2(0.0, 0.0);

            if (attackCounter >= attackRate)
            {
                  Attack();
                  attackCounter = 0.0;
                  animState = NewBornAnimState::NBAS_Attacking;
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

void NewBorn::RenderGameObject(SDL_Renderer *renderer)
{
      if (!isDead)
      {
            CalculateRect();
            switch (animState)
            {
            case NewBornAnimState::NBAS_Crawling:
                  RenderAnimation(renderer, newBornSpriteSheet, 4, rectSize, &newBornAnimIndex, transform.position, false, isFlipped);
                  break;
            case NewBornAnimState::NBAS_Attacking:
                  RenderAnimation(renderer, newBornAttackSpriteSheet, 4, rectSize, &newBornAttackAnimIndex, transform.position, true, isFlipped);
                  if (static_cast<int>(newBornAttackAnimIndex) >= 3)
                  {
                        newBornAttackAnimIndex = 0.0;
                        animState = NewBornAnimState::NBAS_Idle;
                  }
                  break;
            case NewBornAnimState::NBAS_Idle:
                  GameObject::RenderGameObject(renderer);
                  break;
            default:
                  break;
            }
      }
      else
      {
            RenderAnimation(renderer, newBornDeathSpriteSheet, 4, rectSize, &newBornDeathAnimIndex, transform.position, true, isFlipped);
            if (static_cast<int>(newBornDeathAnimIndex) >= 3)
            {
                  canBeDestroyed = true;
            }
      }
}

void NewBorn::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if (otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile")
      {
            isDead = true;
            otherObj->SetCanBeDestroyed(true);
      }
}

void NewBorn::Attack()
{
      if (isDead)
            return;
      refToPlayer->DamagePlayer(10);
}
