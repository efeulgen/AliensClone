
#include "LevelZero.h"

LevelZero::LevelZero(int index, int w, int h) : Level(index, w, h)
{
      Logger::Logg("LevelZero Constructor");

      levelBackgroundPath = "./assets/sprites/Background_1.png";
}

LevelZero::~LevelZero()
{
      Logger::Logg("LevelZero Destructor");
}

void LevelZero::SetupLevel()
{
      // player
      player = new Player(glm::vec2(300, windowHeight * 2 / 3), glm::vec2(600.0, 600.0), 250, this, windowWidth, windowHeight);
      gameObjects.push_back(player);
}
