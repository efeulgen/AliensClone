
#include "AlienEgg.h"

AlienEgg::AlienEgg(glm::vec2 pos, glm::vec2 vel, int rSize) : GameObject(pos, vel, rSize)
{
      Logger::Logg("AlienEgg Constructor");
}

AlienEgg::~AlienEgg()
{
      Logger::Logg("AlienEgg Destructor");
}

void AlienEgg::InitGameObject()
{
}

void AlienEgg::UpdateGameObject(double deltaTime)
{
}

void AlienEgg::CollisionCallback(GameObject *otherObj)
{
}
