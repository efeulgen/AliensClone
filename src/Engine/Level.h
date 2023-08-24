
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <SDL2/SDL.h>
#include "Logger/Logger.h"
#include "GameObject.h"

class Level
{
protected:
      std::vector<GameObject *> gameObjects;
      bool isLevelComplete = false;
      class Player *player = nullptr;

public:
      Level() {}
      virtual ~Level() {}
      virtual void SetupLevel() = 0;

      virtual void UpdateLevel(double deltaTime)
      {
            for (auto obj : gameObjects)
            {
                  obj->UpdateGameObject(deltaTime);
            }
      }

      virtual void RenderLevel(SDL_Renderer *renderer)
      {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            for (auto obj : gameObjects)
            {
                  obj->RenderGameObject(renderer);
            }

            SDL_RenderPresent(renderer);
      }

      // getters & setters
      bool GetIsLevelComplete() const { return isLevelComplete; }
};

#endif
