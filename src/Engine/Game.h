
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Logger/Logger.h"
#include "Managers/GameManager.h"
#include "Managers/LevelManager.h"
#include "Level.h"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
private:
      int millisecsPreviousFrame = 0;

protected:
      SDL_Window *window;
      SDL_Renderer *renderer;
      int windowWidth;
      int windowHeight;

      GameManager *gameManager = nullptr;
      LevelManager *levelManager = nullptr;

public:
      Game();
      ~Game();
      void Init();
      void SetupGame();
      void Display();
      void ProcessInput();
      void Destroy();
      virtual void CreateLevels() {}

      // getters & setters
      int GetWindowWidth() const { return windowWidth; }
      int GetWindowHeight() const { return windowHeight; }

      GameManager *GetGameManager() { return gameManager; }
      LevelManager *GetLevelManager() { return levelManager; }
};

#endif
