
#include "MainMenuUIManager.h"

MainMenuUIManager::MainMenuUIManager(int w, int h) : UIManager(w, h)
{
      Logger::Log("MainMenuUIManager Constructor");
}

MainMenuUIManager::~MainMenuUIManager()
{
      Logger::Log("MainMenuUIManager Destructor");
}

void MainMenuUIManager::RenderUI(SDL_Renderer *renderer)
{
}
