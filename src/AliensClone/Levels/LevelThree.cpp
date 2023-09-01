
#include "LevelThree.h"

LevelThree::LevelThree(int index, int w, int h, int len, GameManager *gManager, bool isFinal) : Level(index, w, h, len, gManager, isFinal)
{
      Logger::Logg("LevelThree Constructor");

      levelBackgroundPath = "./assets/sprites/Background_3.png";
}

LevelThree::~LevelThree()
{
      Logger::Logg("LevelThree Destructor");
}

void LevelThree::SetupLevel()
{
      SDL_ShowCursor(0);

      // player
      player = new Player(glm::vec2(300, windowHeight * 2 / 3), glm::vec2(600.0, 600.0), 250, this, windowWidth, windowHeight);
      gameObjects.push_back(player);

      Level::SetupLevel();
}
