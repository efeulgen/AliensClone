
#include "FacehuggerTank.h"

FacehuggerTank::FacehuggerTank(glm::vec2 pos, int rSize, Player *player) : GameObject(pos, rSize), refToPlayer{player}
{
      Logger::Logg("FacehuggerTank Constructor");

      imgFilePath = undamagedTankImg;
      gameObjectTag = "FacehuggerTank";
}

FacehuggerTank::~FacehuggerTank()
{
      Logger::Logg("FacehuggerTank Destructor");

      refToPlayer = nullptr;
}

void FacehuggerTank::InitGameObject()
{
}

void FacehuggerTank::UpdateGameObject(double deltaTime)
{
      if (refToPlayer->GetPosition().x >= transform.position.x)
      {
            // spawn facehugger
      }
}

void FacehuggerTank::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
}
