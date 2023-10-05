
#include "NewBorn.h"

NewBorn::NewBorn(glm::vec2 pos, int rSize, Player *p, Level *l) : GameObject(pos, rSize), refToPlayer{p}, refToLevel{l}
{
      Logger::Logg("NewBorn Constructor");

      gameObjectTag = "NewBorn";
      velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(newBornSpeed, 0.0) : glm::vec2(-newBornSpeed, 0.0);
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

      // follow player
      if (abs(refToPlayer->GetTransform().position.x - transform.position.x) > attackRange)
      {
            velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(newBornSpeed, 0.0) : glm::vec2(-newBornSpeed, 0.0);
            attackCounter = attackRate;
      }
      else
      {
            velocity = glm::vec2(0.0, 0.0);

            if (attackCounter >= attackRate)
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

void NewBorn::RenderGameObject(SDL_Renderer *renderer)
{
      if (!isDead)
      {
            CalculateRect();
            RenderAnimation(renderer, newBornSpriteSheet, 4, rectSize, &newBornAnimIndex, transform.position, false, isFlipped);
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
      std::cout << "NewBorn attacks." << std::endl;
}
