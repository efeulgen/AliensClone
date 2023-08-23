
#ifndef ALIENSCLONEGAME_H
#define ALIENSCLONEGAME_H

#include "../Engine/Game.h"
#include "LevelZero.h"
#include "LevelOne.h"

class AliensCloneGame : public Game
{
public:
      AliensCloneGame();
      ~AliensCloneGame();

      void SetupLevels() override;
};

#endif
