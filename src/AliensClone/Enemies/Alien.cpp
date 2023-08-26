
#include "Alien.h"

Alien::Alien(glm::vec2 pos, glm::vec2 vel, int rSize) : GameObject(pos, vel, rSize)
{
      Logger::Logg("Alien Constructor");

      gameObjectTag = "Alien";
}

Alien::~Alien()
{
      Logger::Logg("Alien Destructor");
}

void Alien::InitGameObject()
{
}

void Alien::UpdateGameObject(double deltaTime)
{
}

void Alien::Attack()
{
}

void Alien::CollisionCallback(GameObject *otherObj)
{
}
