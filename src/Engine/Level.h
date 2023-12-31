
#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Logger/Logger.h"
#include "GameObject.h"
#include "Managers/AudioManager.h"
#include "Managers/SpawnManager.h"
#include "Managers/UIManager.h"
#include "Managers/GameManager.h"
#include "Managers/GameObjectManager.h"

class Level
{
private:
      int levelIndex;
      int gameObjectCount = 0;

protected:
      GameObjectManager gameObjects;

      bool isLevelComplete = false;
      bool isFinalLevel = false;
      class Player *player = nullptr;
      int levelLength;

      int windowWidth;
      int windowHeight;

      const char *levelBackgroundPath_1;
      const char *levelBackgroundPath_2;
      const char *levelBackgroundPath_3;
      int backgroundXPosition = 0;

      AudioManager *audioManager = nullptr;
      SpawnManager *spawnManager = nullptr;
      UIManager *uiManager = nullptr;
      GameManager *refToGameManager = nullptr;

public:
      Level(int index, int w, int h, int len, GameManager *gManager, bool isFinal = false)
      {
            levelIndex = index;
            windowWidth = w;
            windowHeight = h;
            levelLength = len;
            refToGameManager = gManager;
            isFinalLevel = isFinal;
      }

      virtual ~Level() {}

      virtual void SetupLevelSounds() = 0;
      virtual void SetupLevel()
      {
            // managers
            audioManager = new AudioManager();
            SetupLevelSounds();

            // init game objects
            for (int i = 0; i < gameObjects.GetLength(); i++)
            {
                  gameObjects.GetGameObjects()[i]->InitGameObject();
            }

            gameObjects.SortRenderPriority();
      }

      virtual void UpdateLevel(double deltaTime)
      {
            int i, j;
            for (i = 0; i < gameObjects.GetLength(); i++)
            {
                  GameObject *obj = gameObjects.GetGameObjects()[i];

                  // garbage collection
                  if (obj->GetCanBeDestroyed())
                  {
                        gameObjects.DestroyGameObject(obj);
                        continue;
                  }
                  // update objects
                  obj->UpdateGameObject(deltaTime);

                  // collision detection
                  for (j = 0; j < gameObjects.GetLength(); j++)
                  {
                        GameObject *collider = gameObjects.GetGameObjects()[j];

                        if (i == j)
                        {
                              continue;
                        }
                        else
                        {
                              obj->CheckCollision(collider->GetColliderRect(), collider); // TODO : optimize
                        }
                  }
            }

            // update SpawnManager
            if (levelIndex != 0)
            {
                  spawnManager->UpdateSpawnManager(deltaTime);
            }
      }

      virtual void RenderLevel(SDL_Renderer *renderer)
      {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // *****************************************************************************************************************************
            // ************************* background ****************************************************************************************
            SDL_Surface *surf_1 = IMG_Load(levelBackgroundPath_1);
            SDL_Texture *tex_1 = SDL_CreateTextureFromSurface(renderer, surf_1);
            SDL_Rect rect1 = {backgroundXPosition - windowWidth, 0, windowWidth, windowHeight};
            SDL_RenderCopy(renderer, tex_1, NULL, &rect1);

            SDL_Surface *surf_2 = IMG_Load(levelBackgroundPath_2);
            SDL_Texture *tex_2 = SDL_CreateTextureFromSurface(renderer, surf_2);
            SDL_Rect rect2 = {backgroundXPosition, 0, windowWidth, windowHeight};
            SDL_RenderCopy(renderer, tex_2, NULL, &rect2);

            SDL_Surface *surf_3 = IMG_Load(levelBackgroundPath_3);
            SDL_Texture *tex_3 = SDL_CreateTextureFromSurface(renderer, surf_3);
            SDL_Rect rect3 = {backgroundXPosition + windowWidth, 0, windowWidth, windowHeight};
            SDL_RenderCopy(renderer, tex_3, NULL, &rect3);

            SDL_DestroyTexture(tex_1);
            SDL_DestroyTexture(tex_2);
            SDL_DestroyTexture(tex_3);

            if (backgroundXPosition <= -windowWidth)
            {
                  backgroundXPosition = windowWidth;
            }
            if (backgroundXPosition > windowWidth)
            {
                  backgroundXPosition = (windowWidth * -1);
            }

            // *****************************************************************************************************************************
            // ************************* render objects ************************************************************************************
            for (int i = 0; i < gameObjects.GetLength(); i++)
            {
                  gameObjects.GetGameObjects()[i]->RenderGameObject(renderer);
            }

            // *****************************************************************************************************************************
            // ************************* render UI *****************************************************************************************
            if (refToGameManager->GetIsGameOver())
            {
                  uiManager->RenderGameOverUI(renderer);
            }
            else
            {
                  uiManager->RenderUI(renderer);
            }

            SDL_RenderPresent(renderer);
      }

      // ************************************************************************************************************************************************************************************
      // ************************************************************************************************************************************************************************************
      // ************************************************************************************************************************************************************************************

      virtual void ClearLevelGameObjects()
      {
            gameObjects.ClearGameObjects();
            std::cout << "\033[1;33mLevel " << levelIndex << " GameObject list is cleared.\033[0m" << std::endl;
      }

      virtual void ClearLevelManagers()
      {
            if (audioManager)
            {
                  audioManager->ClearSoundEffects();
                  delete audioManager;
                  audioManager = nullptr;
                  std::cout << "\033[1;33mLevel " << levelIndex << " AudioManager is deleted.\033[0m" << std::endl;
            }
            if (spawnManager)
            {
                  spawnManager->ClearSpawnObjects();
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

      void InstantiateGameObject(GameObject *obj)
      {
            gameObjectCount++;
            obj->SetGameObjectID(gameObjectCount);
            gameObjects.InstantiateGameObject(obj);
            std::cout << obj->GetGameObjectTag() << " has " << obj->GetGameObjectID() << " id." << std::endl; // for debugging, delete later
      }

      void ShifBackground(double shiftValue, double deltaTime)
      {
            backgroundXPosition -= shiftValue * deltaTime;
            for (int i = 0; i < gameObjects.GetLength(); i++)
            {
                  if (gameObjects.GetGameObjects()[i]->GetGameObjectTag() == "Player")
                  {
                        continue;
                  }
                  gameObjects.GetGameObjects()[i]->ShiftGameObject(shiftValue, deltaTime);
            }
      }

      // *************** getters & setters *********************************************
      bool GetIsLevelComplete() const { return isLevelComplete; }
      void SetIsLevelComplete(bool value) { isLevelComplete = value; }

      bool GetIsFinalLevel() const { return isFinalLevel; }
      bool GetIsLevelGameObjectListIsClear() const { return gameObjects.isEmpty(); }
      int GetLevelLength() const { return levelLength; }
      int GetLevelIndex() const { return levelIndex; }

      AudioManager *GetAudioManager() { return audioManager; }
      SpawnManager *GetSpawnManager() { return spawnManager; }
      UIManager *GetUIManager() { return uiManager; }
      GameManager *GetRefToGameManager() { return refToGameManager; }
};

#endif
