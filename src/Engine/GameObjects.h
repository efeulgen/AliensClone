
#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <iostream>
#include <SDL2/SDL.h>
#include "Logger/Logger.h"
#include "GameObject.h"

class GameObjects
{
private:
      int length = 0;
      GameObject **gameObjects = nullptr;

public:
      GameObjects();
      ~GameObjects();

      void InstantiateGameObject(GameObject *newObj);
      GameObject *FindGameObject(GameObject *obj);
      GameObject *FindGameObjectWithTag(std::string tag);
      void DestroyGameObject(GameObject *obj);
      void DestroyGameObjectWithTag(std::string tag);
      void ClearGameObjects();

      // getters & setters
      int GetLength() const { return length; }
      GameObject **GetGameObjects() const { return gameObjects; }
};

#endif
