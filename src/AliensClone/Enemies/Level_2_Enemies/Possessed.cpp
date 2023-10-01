
#include "Possessed.h"

Possessed::Possessed(glm::vec2 pos, int rSize) : GameObject(pos, rSize)
{
      Logger::Logg("Possessed Constructor");
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
}

void Possessed::RenderGameObject(SDL_Renderer *renderer)
{
}

void Possessed::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
}
