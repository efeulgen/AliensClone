
#include "AliensCloneGame.h"

AliensCloneGame::AliensCloneGame()
{
      Logger::Logg("AliensCloneGame Constructor");
}

AliensCloneGame::~AliensCloneGame()
{
      Logger::Logg("AliensCloneGame Destructor");
}

void AliensCloneGame::CreateLevels(GameManager *gameManager)
{
      levelManager->AddLevel(new MainMenu(0, windowWidth, windowHeight, 0, gameManager));
      // levelManager->AddLevel(new LevelOne(1, windowWidth, windowHeight, 15000, gameManager));
      levelManager->AddLevel(new LevelTwo(2, windowWidth, windowHeight, 15000, gameManager));
      levelManager->AddLevel(new LevelThree(3, windowWidth, windowHeight, 15000, gameManager, true));
}
