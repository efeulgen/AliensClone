
#include "NewBorn.h"

NewBorn::NewBorn(glm::vec2 pos, int rSize) : GameObject(pos, rSize)
{
      Logger::Logg("NewBorn Constructor");
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
}

void NewBorn::RenderGameObject(SDL_Renderer *renderer)
{
}

void NewBorn::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
}
