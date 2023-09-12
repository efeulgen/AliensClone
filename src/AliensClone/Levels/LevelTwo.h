
#ifndef LEVELONE_H
#define LEVELONE_H

#include "../../Engine/Level.h"
#include "../Player.h"

class LevelTwo : public Level
{
public:
      LevelTwo(int index, int w, int h, int len, GameManager *gManager, bool isFinal = false);
      ~LevelTwo();

      void SetupLevelSounds() override;
      void SetupLevel() override;
};

#endif
