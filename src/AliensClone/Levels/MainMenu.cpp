
#include "MainMenu.h"

MainMenu::MainMenu(int index, int w, int h, int len, bool isFinal) : Level(index, w, h, len, isFinal)
{
      Logger::Logg("MainMenu Constructor");
}

MainMenu::~MainMenu()
{
      Logger::Logg("MainMenu Destructor");
}

void MainMenu::SetupLevel()
{
      Level::SetupLevel();
}

void MainMenu::RenderLevel(SDL_Renderer *renderer)
{
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      uiManager->RenderImage(renderer, "./assets/sprites/AliensCloneCover.png", glm::vec2(-1, -1));
      uiManager->RenderText(renderer, "Press Any Key", 255, 255, 255, glm::vec2(-1, 700));

      SDL_RenderPresent(renderer);
}
