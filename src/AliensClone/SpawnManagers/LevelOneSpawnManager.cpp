
#include "LevelOneSpawnManager.h"

LevelOneSpawnManager::LevelOneSpawnManager(Player *player, Level *level) : refToPlayer{player}, refToCurrentLevel{level}
{
      Logger::Log("LevelOneSpawnManager Constructor");
}

LevelOneSpawnManager::~LevelOneSpawnManager()
{
      Logger::Log("LevelOneSpawnManager Destructor");
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
                        srand(IncrementSpawnSeed());
                        double alienYPos = 550.0 + static_cast<double>((rand() % 200));
                        double alienXPos = (rand() % 2 == 0) ? 2500.0 : -500.0;

                        Alien *newAlien = new Alien(glm::vec2(alienXPos, alienYPos), 250, refToPlayer, refToCurrentLevel);
                        newAlien->InitGameObject();
                        refToCurrentLevel->InstantiateGameObject(newAlien);
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
                        srand(IncrementSpawnSeed());
                        double huggerYPos = 550.0 + static_cast<double>((rand() % 200));
                        double huggerXPos = (rand() % 2 == 0) ? 2500.0 : -500.0;
                        int spawnHuggerAmount = (rand() % 3) + 1;

                        for (int i = 0; i < spawnHuggerAmount; i++)
                        {
                              Facehugger *newFacehugger = new Facehugger(glm::vec2(huggerXPos + (i * 30), huggerYPos + (i * 50)), 128, refToPlayer, refToCurrentLevel);
                              newFacehugger->InitGameObject();
                              refToCurrentLevel->InstantiateGameObject(newFacehugger);
                        }
                  }
            }
            else
            {
                  spawnObj.spawnCounter += deltaTime;
            }
      }
}
