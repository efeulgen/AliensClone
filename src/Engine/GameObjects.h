
#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <iostream>
#include <SDL2/SDL.h>
#include "Logger/Logger.h"
#include "GameObject.h"

class GameObjects
{
private:
      int size;
      int length;
      GameObject *gameObjects;

public:
      GameObjects(int initSize);
      ~GameObjects();

      void InitGameObjects();
      void UpdateGameObjects(double deltaTime);
      void RenderGameObjects(SDL_Renderer *renderer);

      GameObject FindGameObjectWithTag(std::string tag); // implement with binary search; give indices to game objects
      void RemoveGameObjectWithTag(std::string tag);
      void ClearGameObjects();
};

#endif
