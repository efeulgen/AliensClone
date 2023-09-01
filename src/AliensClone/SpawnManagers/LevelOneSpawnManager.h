
#ifndef LEVELONESPAWNMANAGER_H
#define LEVELONESPAWNMANAGER_H

#include "../../Engine/Managers/SpawnManager.h"
#include "../Enemies/Alien.h"
#include "../Enemies/AlienEgg.h"
#include "../Enemies/Facehugger.h"
#include "../Player.h"

class LevelOneSpawnManager : public SpawnManager
{
private:
      Player *refToPlayer;

public:
      LevelOneSpawnManager(Player *player);
      ~LevelOneSpawnManager();
      GameObject *UpdateSpawnManager(double deltaTime) override;
};

#endif
