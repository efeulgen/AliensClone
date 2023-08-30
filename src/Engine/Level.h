
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Logger/Logger.h"
#include "GameObject.h"

#include "Managers/AudioManager.h"
#include "Managers/LevelManager.h"
#include "Managers/SpawnManager.h"
#include "Managers/UIManager.h"

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

      AudioManager *audioManager = nullptr;
      LevelManager *levelManager = nullptr;
      SpawnManager *spawnManager = nullptr;
      UIManager *uiManager = nullptr;

public:
      Level(int index, int w, int h)
      {
            levelIndex = index;
            windowWidth = w;
            windowHeight = h;
      }
      virtual ~Level() {}
      virtual void SetupLevel()
      {
            for (auto obj : gameObjects)
            {
                  obj->InitGameObject();
            }
      }

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
            SDL_Rect rect3 = {backgroundXPosition - windowWidth, 0, windowWidth, windowHeight};
            SDL_RenderCopy(renderer, tex, NULL, &rect3);
            SDL_DestroyTexture(tex);

            if (backgroundXPosition <= -windowWidth || backgroundXPosition >= windowWidth)
            {
                  backgroundXPosition = 0;
            }

            for (auto obj : gameObjects)
            {
                  obj->RenderGameObject(renderer);
            }

            SDL_RenderPresent(renderer);
      }

      virtual void ClearLevel()
      {
            for (auto obj : gameObjects)
            {
                  obj->DestroyGameObject();
                  obj = nullptr;
            }
            gameObjects.clear();
            std::cout << "\033[1;33mLevel " << levelIndex << " GameObject list is cleared.\033[0m" << std::endl;

            if (audioManager)
            {
                  delete audioManager;
                  audioManager = nullptr;
                  std::cout << "\033[1;33mLevel " << levelIndex << " AudioManager is deleted.\033[0m" << std::endl;
            }
            if (levelManager)
            {
                  delete levelManager;
                  levelManager = nullptr;
                  std::cout << "\033[1;33mLevel " << levelIndex << " LevelManager is deleted.\033[0m" << std::endl;
            }
            if (spawnManager)
            {
                  delete spawnManager;
                  spawnManager = nullptr;
                  std::cout << "\033[1;33mLevel " << levelIndex << " SpawnManager is deleted.\033[0m" << std::endl;
            }
            if (uiManager)
            {
                  delete uiManager;
                  uiManager = nullptr;
                  std::cout << "\033[1;33mLevel " << levelIndex << " UIManager is deleted.\033[0m" << std::endl;
            }
      }

      virtual void InstantiateGameObject(GameObject *obj)
      {
            gameObjects.push_back(obj);
      }

      virtual void ShifBackground(double shiftValue, double deltaTime)
      {
            backgroundXPosition -= shiftValue * deltaTime;
            for (auto obj : gameObjects)
            {
                  if (obj->GetGameObjectTag() == "Player")
                  {
                        continue;
                  }
                  obj->ShiftGameObject(shiftValue, deltaTime);
            }
      }

      // getters & setters
      bool GetIsLevelComplete() const { return isLevelComplete; }
      bool GetIsLevelGameObjectListIsClear() const { return gameObjects.empty(); }

      AudioManager *GetAudioManager() { return audioManager; }
      LevelManager *GetLevelManager() { return levelManager; }
      SpawnManager *GetSpawnManager() { return spawnManager; }
      UIManager *GetUIManager() { return uiManager; }
};

#endif
