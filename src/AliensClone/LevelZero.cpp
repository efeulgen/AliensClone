
#include "LevelZero.h"

LevelZero::LevelZero()
{
      Logger::Logg("LevelZero Constructor");

      levelIndex = 0;
}

LevelZero::~LevelZero()
{
      Logger::Logg("LevelZero Destructor");
}

void LevelZero::SetupLevel()
{
      // player
      player = new Player(glm::vec2(300, 300), glm::vec2(600.0, 600.0), 128, this);
      gameObjects.push_back(player);
}
