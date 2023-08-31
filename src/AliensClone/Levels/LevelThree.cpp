
#include "LevelThree.h"

LevelThree::LevelThree(int index, int w, int h, int len, GameManager *gManager, bool isFinal) : Level(index, w, h, len, gManager, isFinal)
{
      Logger::Logg("LevelThree Constructor");
}

LevelThree::~LevelThree()
{
      Logger::Logg("LevelThree Destructor");
}

void LevelThree::SetupLevel()
{
      SDL_ShowCursor(0);
      // init game objects

      Level::SetupLevel();
}
