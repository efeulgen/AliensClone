
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Logger/Logger.h"
#include "Level.h"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
protected:
      bool isRunning = false;
      int millisecsPreviousFrame = 0;

      SDL_Window *window;
      SDL_Renderer *renderer;
      int windowWidth;
      int windowHeight;

      std::vector<Level *> levels;
      int activeLevelIndex = 0;

public:
      Game();
      ~Game();
      void Init();
      void Display();
      void ProcessInput();
      void Destroy();
      void LoadNextLevel();
      virtual void SetupLevels() {}

      // getters & setters
      int GetWindowWidth() const { return windowWidth; }
      int GetWindowHeight() const { return windowHeight; }
};

#endif
