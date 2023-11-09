
#include "Ladder.h"

Ladder::Ladder(glm::vec2 pos, int rSize) : GameObject(pos, rSize)
{
      Logger::Log("Ladder Constructor");

      imgFilePath = "./assets/sprites/Environment/Ladder.png";
      gameObjectTag = "Ladder";
}

Ladder::~Ladder()
{
      Logger::Log("Ladder Destructor");
}
