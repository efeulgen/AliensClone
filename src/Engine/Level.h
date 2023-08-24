
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

      int windowWidth;
      int windowHeight;

      const char *levelBackground;
      const char *levelGroud;

public:
      Level(int index, int w, int h)
      {
            levelIndex = index;
            windowWidth = w;
            windowHeight = h;
      }
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

            // *****************************************************************************************************************************
            // ************************* dummy ground, background & pillars ****************************************************************
            SDL_SetRenderDrawColor(renderer, 189, 169, 157, 255);
            SDL_Rect backgroundRect = {0, 0, windowWidth, windowHeight};
            SDL_RenderFillRect(renderer, &backgroundRect);

            SDL_SetRenderDrawColor(renderer, 74, 65, 59, 255);
            SDL_Rect groundRect = {0, windowHeight * 5 / 7, windowWidth, windowHeight};
            SDL_RenderFillRect(renderer, &groundRect);

            SDL_Rect dummyPillarRect;
            for (int i = 1; i < 5; i++)
            {
                  SDL_SetRenderDrawColor(renderer, 80, 80, 120, 255);
                  dummyPillarRect = {i * 500, windowHeight * 2 / 5, 50, 250};
                  SDL_RenderFillRect(renderer, &dummyPillarRect);
            }
            // *****************************************************************************************************************************
            // *****************************************************************************************************************************

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
            std::cout << "\033[1;33mLevel " << levelIndex << " GameObject list is cleared.\033[0m" << std::endl;
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
