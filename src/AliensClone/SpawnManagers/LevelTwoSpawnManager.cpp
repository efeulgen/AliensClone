
#include "LevelTwoSpawnManager.h"

LevelTwoSpawnManager::LevelTwoSpawnManager(Player *player, Level *level) : refToPlayer{player}, refToCurrentLevel{level}
{
      Logger::Logg("LevelTwoSpawnManager Constructor");
}

LevelTwoSpawnManager::~LevelTwoSpawnManager()
{
      Logger::Logg("LevelTwoSpawnManager Destructor");
}

void LevelTwoSpawnManager::UpdateSpawnManager(double deltaTime)
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
                  if (spawnObj.gameObjectTag == "NewBorn")
                  {
                        /*
                        srand(IncrementSpawnSeed());
                        double newBornYPos = 650.0 + static_cast<double>((rand() % 200));

                        NewBorn *newNewBorn = new NewBorn(glm::vec2(3000.0, newBornYPos), 120, refToPlayer, refToCurrentLevel);
                        newNewBorn->InitGameObject();
                        refToCurrentLevel->InstantiateGameObject(newNewBorn);
                        */
                  }
                  else if (spawnObj.gameObjectTag == "Possessed")
                  {
                        /*
                        srand(IncrementSpawnSeed());
                        double possessedYPos = 500.0 + static_cast<double>((rand() % 200));

                        Possessed *newPossessed = new Possessed(glm::vec2(3000.0, possessedYPos), 250, refToPlayer, refToCurrentLevel);
                        newPossessed->InitGameObject();
                        refToCurrentLevel->InstantiateGameObject(newPossessed);
                        */
                  }
                  else if (spawnObj.gameObjectTag == "Blob")
                  {
                        srand(IncrementSpawnSeed());
                        double possessedYPos = 50.0 + static_cast<double>((rand() % 100));

                        Blob *newBlob = new Blob(glm::vec2(2000.0, possessedYPos), glm::vec2(-40, 0), 128, refToPlayer, refToCurrentLevel);
                        newBlob->InitGameObject();
                        refToCurrentLevel->InstantiateGameObject(newBlob);
                  }
            }
            else
            {
                  spawnObj.spawnCounter += deltaTime;
            }
      }
}
