
#include "LevelOneSpawnManager.h"

LevelOneSpawnManager::LevelOneSpawnManager(Player *player, Level *level) : refToPlayer{player}, refToCurrentLevel{level}
{
      Logger::Logg("LevelOneSpawnManager Constructor");
}

LevelOneSpawnManager::~LevelOneSpawnManager()
{
      Logger::Logg("LevelOneSpawnManager Destructor");
}

void LevelOneSpawnManager::UpdateSpawnManager(double deltaTime)
{
      if (refToCurrentLevel->GetRefToGameManager()->GetIsGameOver())
      {
            return;
      }

      for (auto &spawnObj : spawnObjects)
      {
            if (spawnObj.spawnCounter >= spawnObj.spawnRate)
            {
                  spawnObj.spawnCounter = 0.0;
                  if (spawnObj.gameObjectTag == "Alien")
                  {
                        /*
                        srand(IncrementSpawnSeed());
                        double alienYPos = 550.0 + static_cast<double>((rand() % 200));

                        Alien *newAlien = new Alien(glm::vec2(3000.0, alienYPos), 250, refToPlayer, refToCurrentLevel);
                        newAlien->InitGameObject();
                        refToCurrentLevel->InstantiateGameObject(newAlien);
                        */
                  }
                  else if (spawnObj.gameObjectTag == "AlienEgg")
                  {
                        srand(IncrementSpawnSeed());
                        double alienEggSpawnOffset = (rand() % 3) == 0 ? 700.0 : -700.0;

                        AlienEgg *newAlienEgg = new AlienEgg(glm::vec2(refToPlayer->GetPosition().x + alienEggSpawnOffset, -100.0), glm::vec2(0.0, 375.0), 200, refToCurrentLevel, refToPlayer);
                        newAlienEgg->InitGameObject();
                        refToCurrentLevel->InstantiateGameObject(newAlienEgg);
                  }
                  else if (spawnObj.gameObjectTag == "Facehugger")
                  {
                        std::cout << "Spawn Facehugger" << std::endl;
                  }
            }
            else
            {
                  spawnObj.spawnCounter += deltaTime;
            }
      }
}
