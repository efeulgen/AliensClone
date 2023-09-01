
#ifndef LEVELTHREESPAWNMANAGER_H
#define LEVELTHREESPAWNMANAGER_H

#include "../../Engine/Managers/SpawnManager.h"

class LevelThreeSpawnManager : public SpawnManager
{
public:
      LevelThreeSpawnManager();
      ~LevelThreeSpawnManager();
      GameObject *UpdateSpawnManager(double deltaTime) override;
};

#endif
