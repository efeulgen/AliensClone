
#include "AliensCloneGame.h"

AliensCloneGame::AliensCloneGame()
{
      Logger::Logg("AliensCloneGame Constructor");
}

AliensCloneGame::~AliensCloneGame()
{
      Logger::Logg("AliensCloneGame Destructor");
}

void AliensCloneGame::SetupLevels()
{
      levels.push_back(new LevelZero(0, windowWidth, windowHeight));
      levels.push_back(new LevelOne(1, windowWidth, windowHeight));
}
