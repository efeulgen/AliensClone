
#include "AliensCloneGame.h"

AliensCloneGame::AliensCloneGame()
{
      Logger::Logg("AliensCloneGame Constructor");
}

AliensCloneGame::~AliensCloneGame()
{
      Logger::Logg("AliensCloneGame Destructor");
}

void AliensCloneGame::CreateLevels()
{
      levelManager->AddLevel(new MainMenu(0, windowWidth, windowHeight, 0));
      levelManager->AddLevel(new LevelOne(1, windowWidth, windowHeight, 15000));
      levelManager->AddLevel(new LevelTwo(2, windowWidth, windowHeight, 15000, true));
}
