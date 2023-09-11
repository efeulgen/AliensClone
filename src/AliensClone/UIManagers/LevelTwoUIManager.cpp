
#include "LevelTwoUIManager.h"

LevelTwoUIManager::LevelTwoUIManager(int w, int h) : UIManager(w, h)
{
      Logger::Logg("LevelTwoUIManager Constructor");
}
LevelTwoUIManager::~LevelTwoUIManager()
{
      Logger::Logg("LevelTwoUIManager Destructor");
}

void LevelTwoUIManager::RenderUI(SDL_Renderer *renderer)
{
}