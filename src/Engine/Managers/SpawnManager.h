
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
protected:
      std::vector<SpawnObject> spawnObjects;

public:
      SpawnManager() {}
      virtual ~SpawnManager() {}

      virtual GameObject *UpdateSpawnManager(double deltaTime) = 0;

      void SpawnGameObject(std::string tag, double rate)
      {
            SpawnObject spawnObj = {tag, rate, rate};
            spawnObjects.push_back(spawnObj);
      }

      void ClearSpawnObjects()
      {
            spawnObjects.clear();
      }
};

#endif
