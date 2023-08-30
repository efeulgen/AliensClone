
#include "LevelManager.h"

LevelManager::LevelManager()
{
      Logger::Logg("LevelManager Constructor");
}

LevelManager::~LevelManager()
{
      Logger::Logg("LevelManager Destructor");
}

void LevelManager::LoadNextLevel()
{
      levels[activeLevelIndex]->ClearLevelGameObjects();
      levels[activeLevelIndex]->ClearLevelManagers();

      activeLevelIndex++;

      levels[activeLevelIndex]->SetupLevel();
}

void LevelManager::LoadMainMenu()
{
      levels[activeLevelIndex]->ClearLevelGameObjects();
      levels[activeLevelIndex]->ClearLevelManagers();

      activeLevelIndex = 0;

      levels[activeLevelIndex]->SetupLevel();
}

void LevelManager::RestartLevel()
{
      levels[activeLevelIndex]->ClearLevelGameObjects();
      levels[activeLevelIndex]->ClearLevelManagers();
      levels[activeLevelIndex]->SetupLevel();
}

void LevelManager::AddLevel(Level *level)
{
      levels.push_back(level);
}

void LevelManager::ClearLevels()
{
      if (!levels.empty())
      {
            for (auto level : levels)
            {
                  if (!level)
                        continue;
                  if (!level->GetIsLevelGameObjectListIsClear())
                  {
                        level->ClearLevelGameObjects();
                  }
                  level->ClearLevelManagers();
                  delete level;
                  level = nullptr;
            }
            levels.clear();
      }
}
