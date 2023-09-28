
#ifndef LEVELTWOSPAWNMANAGER_H
#define LEVELTWOSPAWNMANAGER_H

#include "../../Engine/Managers/SpawnManager.h"

class LevelTwoSpawnManager : public SpawnManager
{
public:
      LevelTwoSpawnManager();
      ~LevelTwoSpawnManager();
      GameObject *UpdateSpawnManager(double deltaTime) override;
};

#endif