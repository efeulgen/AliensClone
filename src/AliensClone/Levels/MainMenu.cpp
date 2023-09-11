
#include "MainMenu.h"

MainMenu::MainMenu(int index, int w, int h, int len, GameManager *gManager, bool isFinal) : Level(index, w, h, len, gManager, isFinal)
{
      Logger::Logg("MainMenu Constructor");
}

MainMenu::~MainMenu()
{
      Logger::Logg("MainMenu Destructor");
}

void MainMenu::SetupLevel()
{
      SDL_ShowCursor(1);

      uiManager = new MainMenuUIManager(windowWidth, windowHeight);
      Level::SetupLevel();
}

void MainMenu::RenderLevel(SDL_Renderer *renderer)
{
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      uiManager->RenderImage(renderer, "./assets/sprites/AliensCloneCover.png", glm::vec2(-1, -1));
      uiManager->RenderText(renderer, "Press Space", 255, 255, 255, glm::vec2(-1, 750));

      SDL_RenderPresent(renderer);
}
