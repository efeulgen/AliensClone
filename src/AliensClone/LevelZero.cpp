
#include "LevelZero.h"

LevelZero::LevelZero()
{
      Logger::Logg("LevelZero Constructor");
}

LevelZero::~LevelZero()
{
      Logger::Logg("LevelZero Destructor");
}

void LevelZero::SetupLevel()
{
      // player
      player = new Player(glm::vec2(300, 300), glm::vec2(5.0, 5.0));
      gameObjects.push_back(player);
}
