
#include "FacehuggerTank.h"

FacehuggerTank::FacehuggerTank(glm::vec2 pos, int rSize, Player *player) : GameObject(pos, rSize), refToPlayer{player}
{
      Logger::Logg("FacehuggerTank Constructor");
}

FacehuggerTank::~FacehuggerTank()
{
      Logger::Logg("FacehuggerTank Destructor");
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

void FacehuggerTank::CollisionCallback(GameObject *otherObj)
{
}
