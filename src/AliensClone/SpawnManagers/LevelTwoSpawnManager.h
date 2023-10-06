
#ifndef LEVELTWOSPAWNMANAGER_H
#define LEVELTWOSPAWNMANAGER_H

#include "../../Engine/Managers/SpawnManager.h"
#include "../../Engine/Level.h"
#include "../Player.h"
#include "../Enemies/Level_2_Enemies/NewBorn.h"
#include "../Enemies/Level_2_Enemies/Possessed.h"

class LevelTwoSpawnManager : public SpawnManager
{
private:
      Player *refToPlayer;
      Level *refToCurrentLevel;

public:
      LevelTwoSpawnManager(Player *player, Level *level);
      ~LevelTwoSpawnManager();
      void UpdateSpawnManager(double deltaTime) override;
};

#endif
