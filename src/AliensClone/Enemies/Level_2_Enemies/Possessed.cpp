
#include "Possessed.h"

Possessed::Possessed(glm::vec2 pos, int rSize, Player *p, Level *l) : GameObject(pos, rSize), refToPlayer{p}, refToLevel{l}
{
      Logger::Logg("Possessed Constructor");

      gameObjectTag = "Possessed";
      velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(possessedSpeed, 0.0) : glm::vec2(-possessedSpeed, 0.0);
      animState = PossessedAnimState::POSAS_Walking;
}

Possessed::~Possessed()
{
      Logger::Logg("Possessed Destructor");
}

void Possessed::InitGameObject()
{
}

void Possessed::UpdateGameObject(double deltaTime)
{
      if (refToLevel->GetRefToGameManager()->GetIsGameOver())
            return;

      // anims
      possessedWalkAnimIndex += deltaTime * 10;

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
      CalculateRect();
      RenderAnimation(renderer, possessedWalkSpriteSheet, 4, rectSize, &possessedWalkAnimIndex, transform.position, false, isFlipped);
}

void Possessed::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if (otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile")
      {
            otherObj->SetCanBeDestroyed(true);
      }
}

void Possessed::Attack()
{
      std::cout << "Possessed Attacks" << std::endl;
}
