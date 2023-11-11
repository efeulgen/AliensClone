
#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include <iostream>
#include <SDL2/SDL.h>
#include "../Logger/Logger.h"
#include "../GameObject.h"

class GameObjectManager
{
private:
      int length = 0;
      GameObject **gameObjects = nullptr;

public:
      GameObjectManager();
      ~GameObjectManager();

      void InstantiateGameObject(GameObject *newObj);
      GameObject *FindGameObject(GameObject *obj);
      GameObject *FindGameObjectWithTag(std::string tag);
      void DestroyGameObject(GameObject *obj);
      void DestroyGameObjectWithTag(std::string tag);
      void ClearGameObjects();
      void SortRenderPriority();
      bool isEmpty() const;

      // *************** getters *********************************************
      int GetLength() const { return length; }
      GameObject **GetGameObjects() const { return gameObjects; }
};

#endif
