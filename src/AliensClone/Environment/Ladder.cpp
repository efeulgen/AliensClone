
#include "Ladder.h"

Ladder::Ladder(glm::vec2 pos, int rSizeX, int rSizeY) : GameObject(pos, rSizeX, rSizeY)
{
      Logger::Log("Ladder Constructor");

      imgFilePath = "./assets/sprites/Environment/Ladder_rectangular.png";
      gameObjectTag = "Ladder";
}

Ladder::~Ladder()
{
      Logger::Log("Ladder Destructor");
}
