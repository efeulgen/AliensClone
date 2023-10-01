
#include "Blob.h"

Blob::Blob(glm::vec2 pos, int rSize) : GameObject(pos, rSize)
{
      Logger::Logg("Blob Constructor");
}

Blob::~Blob()
{
      Logger::Logg("Blob Destructor");
}

void Blob::InitGameObject()
{
}

void Blob::UpdateGameObject(double deltaTime)
{
}

void Blob::RenderGameObject(SDL_Renderer *renderer)
{
}

void Blob::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
}
