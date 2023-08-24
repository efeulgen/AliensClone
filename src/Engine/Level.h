
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
      int levelIndex;

public:
      Level() {}
      virtual ~Level() {}
      virtual void SetupLevel() = 0;

      virtual void UpdateLevel(double deltaTime)
      {
            for (auto obj : gameObjects)
            {
                  if (obj->GetCanBeDestroyed())
                  {
                        gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
                        obj->DestroyGameObject();
                        obj = nullptr;
                        break;
                  }
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

      virtual void ClearLevelGameObjects()
      {
            for (auto obj : gameObjects)
            {
                  obj->DestroyGameObject();
                  obj = nullptr;
            }
            gameObjects.clear();
            std::cout << "Level " << levelIndex << " GameObject list is cleared." << std::endl;
      }

      virtual void InstantiateGameObject(GameObject *obj)
      {
            gameObjects.push_back(obj);
      }

      // getters & setters
      bool GetIsLevelComplete() const { return isLevelComplete; }
      bool GetIsLevelGameObjectListIsClear() const { return gameObjects.empty(); }
};

#endif
