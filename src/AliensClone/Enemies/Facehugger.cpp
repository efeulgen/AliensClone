
#include "Facehugger.h"

Facehugger::Facehugger(glm::vec2 pos, glm::vec2 vel, int rSize) : GameObject(pos, vel, rSize)
{
      Logger::Logg("Facehugger Constructor");

      gameObjectTag = "Facehugger";
}

Facehugger::~Facehugger()
{
      Logger::Logg("Facehugger Destructor");
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
            canBeDestroyed = true;
            otherObj->SetCanBeDestroyed(true);
      }

      if (otherObj->GetGameObjectTag() == "Player")
      {
            // facehug player
      }
}