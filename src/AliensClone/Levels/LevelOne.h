
#ifndef LEVELZERO_H
#define LEVELZERO_H

#include "../../Engine/Level.h"
#include "../Player.h"
#include "../Enemies/Alien.h"
#include "../Pickups/Pickup.h"
#include "../SpawnManagers/LevelOneSpawnManager.h"
#include "../UIManagers/LevelOneUIManager.h"

class LevelOne : public Level
{
public:
      LevelOne(int index, int w, int h, int len, GameManager *gManager, bool isFinal = false);
      ~LevelOne();

      void SetupLevelSounds() override;
      void SetupLevel() override;
};

#endif
