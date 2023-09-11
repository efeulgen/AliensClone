
#include "MainMenuUIManager.h"

MainMenuUIManager::MainMenuUIManager(int w, int h) : UIManager(w, h)
{
      Logger::Logg("MainMenuUIManager Constructor");
}

MainMenuUIManager::~MainMenuUIManager()
{
      Logger::Logg("MainMenuUIManager Destructor");
}

void MainMenuUIManager::RenderUI(SDL_Renderer *renderer)
{
}
