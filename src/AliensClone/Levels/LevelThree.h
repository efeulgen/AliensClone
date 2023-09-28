
#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "../../Engine/Level.h"
#include "../Player.h"
#include "../SpawnManagers/LevelThreeSpawnManager.h"
#include "../UIManagers/LevelThreeUIManager.h"

class LevelThree : public Level
{
public:
      LevelThree(int index, int w, int h, int len, GameManager *gManager, bool isFinal = false);
      ~LevelThree();

      void SetupLevelSounds() override;
      void SetupLevel() override;
};

#endif
