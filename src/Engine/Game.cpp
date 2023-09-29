
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

      TTF_Init();

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

      gameMusic = Mix_LoadWAV("./audio/game_music.wav");
      Mix_VolumeChunk(gameMusic, 35);
      Mix_PlayChannel(-1, gameMusic, -1);

      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Game::SetupGame()
{
      gameManager = new GameManager();
      gameManager->SetIsRunning(true);

      levelManager = new LevelManager();

      CreateLevels(gameManager);
}

void Game::Display()
{
      // *****************************************************************************************************************************
      levelManager->GetCurrentLevel()->SetupLevel();
      while (gameManager->GetIsRunning())
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
            levelManager->GetCurrentLevel()->UpdateLevel(deltaTime);
            levelManager->GetCurrentLevel()->RenderLevel(renderer);

            if (levelManager->GetCurrentLevel()->GetIsLevelComplete())
            {
                  if (levelManager->GetCurrentLevel()->GetIsFinalLevel())
                  {
                        levelManager->LoadMainMenu();
                  }
                  else
                  {
                        levelManager->LoadNextLevel();
                  }
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
                  gameManager->SetIsRunning(false);
            }
            if (event.type == SDL_KEYDOWN)
            {
                  if (event.key.keysym.sym == SDLK_SPACE && levelManager->GetActiveLevelIndex() == 0)
                  {
                        levelManager->LoadNextLevel();
                        gameManager->SetIsGameStarted(true);
                  }
                  if (event.key.keysym.sym == SDLK_SPACE && gameManager->GetIsGameOver())
                  {
                        levelManager->LoadMainMenu();
                        gameManager->SetIsGameOver(false);
                        gameManager->SetIsPlayerDead(false);
                        gameManager->SetIsGameStarted(false);
                  }
                  if (event.key.keysym.sym == SDLK_ESCAPE)
                  {
                        Logger::Err("Quit Game");
                        gameManager->SetIsRunning(false);
                  }
            }
      }
}

void Game::Destroy()
{
      Mix_FreeChunk(gameMusic);
      gameMusic = nullptr;

      levelManager->ClearLevels();

      delete levelManager;
      levelManager = nullptr;
      delete gameManager;
      gameManager = nullptr;

      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
}
