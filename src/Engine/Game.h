
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "Logger/Logger.h"
#include "Level.h"

class Game
{
private:
      bool isRunning;
      double deltaTime;
      int millisecsPreviousFrame;

      SDL_Window *window;
      SDL_Renderer *renderer;

      std::vector<Level *> levels;

public:
      Game();
      ~Game();
      void Init();
      void Display();
      void ProcessInput();
      void Destroy();
};

#endif
