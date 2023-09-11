
#ifndef LEVELONESPAWNMANAGER_H
#define LEVELONESPAWNMANAGER_H

#include "../../Engine/Managers/SpawnManager.h"
#include "../../Engine/Level.h"
#include "../Enemies/Alien.h"
#include "../Enemies/AlienEgg.h"
#include "../Enemies/Facehugger.h"
#include "../Player.h"

class LevelOneSpawnManager : public SpawnManager
{
private:
      Player *refToPlayer;
      Level *refToCurrentLevel;

public:
      LevelOneSpawnManager(Player *player, Level* level);
      ~LevelOneSpawnManager();
      GameObject *UpdateSpawnManager(double deltaTime) override;
};

#endif
