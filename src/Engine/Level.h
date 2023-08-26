
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

      const char *levelBackgroundPath;
      int backgroundXPosition = 0;

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

                  // collision detection
                  for (auto collider : gameObjects)
                  {
                        if (obj == collider)
                        {
                              continue;
                        }
                        else
                        {
                              obj->CheckCollision(collider->GetRect(), collider);
                        }
                  }
            }
      }

      virtual void RenderLevel(SDL_Renderer *renderer)
      {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // *****************************************************************************************************************************
            // ************************* background ****************************************************************************************
            SDL_Surface *surf = IMG_Load(levelBackgroundPath);
            SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_Rect rect1 = {backgroundXPosition, 0, windowWidth, windowHeight};
            SDL_RenderCopy(renderer, tex, NULL, &rect1);
            SDL_Rect rect2 = {backgroundXPosition + windowWidth, 0, windowWidth, windowHeight};
            SDL_RenderCopy(renderer, tex, NULL, &rect2);
            SDL_DestroyTexture(tex);

            if (backgroundXPosition <= -windowWidth)
            {
                  backgroundXPosition = 0;
            }

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

      virtual void ShifBackground(double shiftValue, double deltaTime)
      {
            backgroundXPosition -= shiftValue * deltaTime;
      }

      // getters & setters
      bool GetIsLevelComplete() const { return isLevelComplete; }
      bool GetIsLevelGameObjectListIsClear() const { return gameObjects.empty(); }
};

#endif
