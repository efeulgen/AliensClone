
#include "Facehugger.h"

Facehugger::Facehugger(glm::vec2 pos, int rSize, Player *p, Level *l) : GameObject(pos, rSize), refToPlayer{p}, refToCurrentLevel{l}
{
      Logger::Logg("Facehugger Constructor");

      gameObjectTag = "Facehugger";

      velocity = refToPlayer->GetTransform().position.x > transform.position.x ? glm::vec2(facehuggerSpeed, 0.0) : glm::vec2(-facehuggerSpeed, 0.0);
}

Facehugger::~Facehugger()
{
      Logger::Logg("Facehugger Destructor");

      refToPlayer = nullptr;
      refToCurrentLevel = nullptr;
}

void Facehugger::InitGameObject()
{
}

void Facehugger::UpdateGameObject(double deltaTime)
{
      if (refToCurrentLevel->GetRefToGameManager()->GetIsGameOver())
            return;

      facehuggerWalkAnimIndex += deltaTime * 8;

      isFlipped = refToPlayer->GetTransform().position.x > transform.position.x ? true : false;

      transform.position.x += velocity.x * deltaTime;
      transform.position.y += velocity.y * deltaTime;
}

void Facehugger::RenderGameObject(SDL_Renderer *renderer)
{
      CalculateRect();
      RenderAnimation(renderer, facehuggerWalkSpriteSheet, 4, rectSize, &facehuggerWalkAnimIndex, transform.position, false, isFlipped);
}

void Facehugger::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if (otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile")
      {
            otherObj->SetCanBeDestroyed(true);
            refToCurrentLevel->GetAudioManager()->PlaySFX(9);
            canBeDestroyed = true;
      }

      if (otherObj->GetGameObjectTag() == "Player")
      {
            static_cast<Player *>(otherObj)->ActivateIsFacehugged();
            canBeDestroyed = true;
      }
}