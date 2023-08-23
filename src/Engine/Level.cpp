
#include "Level.h"

Level::Level()
{
      Logger::Logg("Level Constructor");

      isLevelComplete = false;
}

Level::~Level()
{
      Logger::Logg("Level Destrcutor");
}

void Level::SetupLevel()
{
}

void Level::UpdateLevel(double deltaTime)
{
}

void Level::RenderLevel(SDL_Renderer *renderer)
{
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      for (auto obj : gameObjects)
      {
            obj->RenderGameObject(renderer);
      }
}