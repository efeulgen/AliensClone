
#include "MachinegunPossessed.h"

MachinegunPossessed::MachinegunPossessed(glm::vec2 pos, int rSize) : GameObject(pos, rSize)
{
      Logger::Logg("MachinegunPossessed Constructor");
}

MachinegunPossessed::~MachinegunPossessed()
{
      Logger::Logg("MachinegunPossessed Destrcutor");
}

void MachinegunPossessed::InitGameObject()
{
}

void MachinegunPossessed::UpdateGameObject(double deltaTime)
{
}

void MachinegunPossessed::RenderGameObject(SDL_Renderer *renderer)
{
}

void MachinegunPossessed::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
}
