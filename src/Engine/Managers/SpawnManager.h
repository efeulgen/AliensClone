
#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "../Logger/Logger.h"
#include "../GameObject.h"

struct SpawnObject
{
      std::string gameObjectTag;
      double spawnRate;
      double spawnCounter;
};

class SpawnManager
{
private:
      int spawnSeed = 0;

protected:
      std::vector<SpawnObject> spawnObjects;

public:
      SpawnManager() {}
      virtual ~SpawnManager() {}

      virtual void UpdateSpawnManager(double deltaTime) = 0;

      void CreateSpawnObject(std::string tag, double rate)
      {
            SpawnObject spawnObj = {tag, rate, rate};
            spawnObjects.push_back(spawnObj);
      }

      void ClearSpawnObjects()
      {
            spawnObjects.clear();
      }

      // getters & setters
      int GetSpawnSeed() const { return spawnSeed; }
      int IncrementSpawnSeed() { return spawnSeed++; }
};

#endif
