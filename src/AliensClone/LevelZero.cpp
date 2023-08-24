
#include "LevelZero.h"

LevelZero::LevelZero(int index, int w, int h) : Level(index, w, h)
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
      player = new Player(glm::vec2(300, 500), glm::vec2(600.0, 600.0), 128, this, windowWidth, windowHeight);
      gameObjects.push_back(player);
}
