
#include "LevelThreeUIManager.h"

LevelThreeUIManager::LevelThreeUIManager(int w, int h) : UIManager(w, h)
{
      Logger::Logg("LevelThreeUIManager Constructor");
}

LevelThreeUIManager::~LevelThreeUIManager()
{
      Logger::Logg("LevelThreeUIManager Destructor");
}

void LevelThreeUIManager::RenderUI(SDL_Renderer *renderer)
{
}
