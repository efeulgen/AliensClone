
#include "Facehugger.h"

Facehugger::Facehugger(glm::vec2 pos, int rSize, Player *p, Level *l) : GameObject(pos, rSize), refToPlayer{p}, refToCurrentLevel{l}
{
      Logger::Logg("Facehugger Constructor");

      imgFilePath = ""; // create sprite
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
}

void Facehugger::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if (otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile")
      {
            otherObj->SetCanBeDestroyed(true);
            canBeDestroyed = true;
      }

      if (otherObj->GetGameObjectTag() == "Player")
      {
            static_cast<Player *>(otherObj)->ActivateIsFacehugged();
            canBeDestroyed = true;
      }
}