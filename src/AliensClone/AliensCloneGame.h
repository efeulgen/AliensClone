
#ifndef ALIENSCLONEGAME_H
#define ALIENSCLONEGAME_H

#include "../Engine/Game.h"
#include "Levels/MainMenu.h"
#include "Levels/LevelOne.h"
#include "Levels/LevelTwo.h"
#include "Levels/LevelThree.h"

class AliensCloneGame : public Game
{
public:
      AliensCloneGame();
      ~AliensCloneGame();

      void CreateLevels(GameManager *gameManager) override;
};

#endif
