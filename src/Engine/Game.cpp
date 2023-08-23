
#include "Game.h"

Game::Game()
{
      Logger::Logg("Game Constructor");

      isRunning = false;
      deltaTime = 0.0;
      millisecsPreviousFrame = 0;
      activeLevelIndex = 0;
}

Game::~Game()
{
      Logger::Logg("Game Destructor");
}

void Game::Init()
{
      if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
      {
            Logger::Err("SDL initialization fails.");
            return;
      }

      window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_BORDERLESS);
      if (!window)
      {
            Logger::Err("SDL_Window creation fails.");
            return;
      }

      renderer = SDL_CreateRenderer(window, -1, 0);
      if (!renderer)
      {
            Logger::Err("SDL_Renderer creation fails.");
            SDL_DestroyWindow(window);
            return;
      }

      // setup game
      isRunning = true;
      SetupLevels();
}

void Game::Display()
{
      // *****************************************************************************************************************************
      // ************************* deltaTime *****************************************************************************************
      int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
      if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
      {
            SDL_Delay(timeToWait);
      }
      deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
      millisecsPreviousFrame = SDL_GetTicks();

      // *****************************************************************************************************************************
      levels[activeLevelIndex]->SetupLevel();
      while (isRunning)
      {
            ProcessInput();
            levels[activeLevelIndex]->UpdateLevel(deltaTime);
            levels[activeLevelIndex]->RenderLevel(renderer);

            if (levels[activeLevelIndex]->GetIsLevelComplete())
            {
                  LoadNextLevel();
            }
      }
}

void Game::ProcessInput()
{
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
            if (event.type == SDL_QUIT)
            {
                  isRunning = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                  if (event.key.keysym.sym == SDLK_ESCAPE)
                  {
                        isRunning = false;
                  }
            }
      }
}

void Game::Destroy()
{
      if (!levels.empty())
      {
            for (auto level : levels)
            {
                  delete level;
                  level = nullptr;
            }
      }

      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
}

void Game::LoadNextLevel()
{
      std::cout << "Load Next Level" << std::endl;
}
