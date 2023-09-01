
#include "LevelOneSpawnManager.h"

LevelOneSpawnManager::LevelOneSpawnManager(Player *player) : refToPlayer{player}
{
      Logger::Logg("LevelOneSpawnManager Constructor");
}

LevelOneSpawnManager::~LevelOneSpawnManager()
{
      Logger::Logg("LevelOneSpawnManager Destructor");
}

GameObject *LevelOneSpawnManager::UpdateSpawnManager(double deltaTime)
{
      for (auto &spawnObj : spawnObjects)
      {
            if (spawnObj.spawnCounter >= spawnObj.spawnRate)
            {
                  spawnObj.spawnCounter = 0.0;
                  if (spawnObj.gameObjectTag == "Alien")
                  {
                        return new Alien(glm::vec2(3000, 700), 250, refToPlayer);
                  }
                  else if (spawnObj.gameObjectTag == "AlienEgg")
                  {
                        std::cout << "Spawn AlienEgg" << std::endl;
                        return nullptr;
                  }
                  else if (spawnObj.gameObjectTag == "Facehugger")
                  {
                        std::cout << "Spawn Facehugger" << std::endl;
                        return nullptr;
                  }
            }
            else
            {
                  spawnObj.spawnCounter += deltaTime;
            }
      }
      return nullptr;
}
