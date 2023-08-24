
#include "LevelOne.h"

LevelOne::LevelOne(int index, int w, int h) : Level(index, w, h)
{
      Logger::Logg("LevelOne Constructor");
}

LevelOne::~LevelOne()
{
      Logger::Logg("LevelOne Destructor");
}

void LevelOne::SetupLevel()
{
}
