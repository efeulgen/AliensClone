
#include "Game.h"

Game::Game()
{
      Logger::Logg("Game Constructor");
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

      if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
      {
            Logger::Err("SDL_Mixer initialization fails.");
      }

      SDL_DisplayMode displayMode;
      SDL_GetCurrentDisplayMode(0, &displayMode);
      windowWidth = displayMode.w;
      windowHeight = displayMode.h;
      window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);
      if (!window)
      {
            Logger::Err("SDL_Window creation fails.");
            return;
      }
      SDL_GetWindowSize(window, &windowWidth, &windowHeight);

      renderer = SDL_CreateRenderer(window, -1, 0);
      if (!renderer)
      {
            Logger::Err("SDL_Renderer creation fails.");
            SDL_DestroyWindow(window);
            return;
      }

      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

      // setup game
      isRunning = true;
      SetupLevels();
}

void Game::Display()
{
      // *****************************************************************************************************************************
      levels[activeLevelIndex]->SetupLevel();
      while (isRunning)
      {
            // *****************************************************************************************************************************
            // ************************* deltaTime *****************************************************************************************
            int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
            if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
            {
                  SDL_Delay(timeToWait);
            }
            double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
            millisecsPreviousFrame = SDL_GetTicks();

            // *****************************************************************************************************************************
            // ************************* game loop *****************************************************************************************
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
                  if (!level->GetIsLevelGameObjectListIsClear())
                  {
                        level->ClearLevelGameObjects();
                  }
                  delete level;
                  level = nullptr;
            }
            levels.clear();
      }

      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
}

void Game::LoadNextLevel()
{
      std::cout << "Load Next Level" << std::endl;
}
