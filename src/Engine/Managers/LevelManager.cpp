
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
      currentLevel->level->ClearLevelGameObjects();
      currentLevel->level->ClearLevelManagers();

      currentLevel = currentLevel->nextLevel;
      currentLevel->level->SetupLevel();
}

void LevelManager::LoadMainMenu()
{
      currentLevel->level->ClearLevelGameObjects();
      currentLevel->level->ClearLevelManagers();

      LevelNode *temp = firstLevel;
      while (temp)
      {
            temp->level->SetIsLevelComplete(false);
            temp = temp->nextLevel;
      }

      currentLevel = firstLevel;
      firstLevel->level->SetupLevel();
}

void LevelManager::RestartLevel()
{
      currentLevel->level->ClearLevelGameObjects();
      currentLevel->level->ClearLevelManagers();
      currentLevel->level->SetupLevel();
}

void LevelManager::AddLevel(Level *level)
{
      LevelNode *newLevel = new LevelNode;
      newLevel->level = level;
      newLevel->nextLevel = nullptr;

      if (firstLevel == nullptr)
      {
            firstLevel = lastLevel = currentLevel = newLevel;
      }
      else
      {
            lastLevel->nextLevel = newLevel;
            lastLevel = newLevel;
      }
}

void LevelManager::ClearLevels()
{
      LevelNode *temp = firstLevel;
      while (temp)
      {
            if (!temp->level->GetIsLevelGameObjectListIsClear())
            {
                  temp->level->ClearLevelGameObjects();
            }
            temp->level->ClearLevelManagers();
            delete temp->level;
            temp->level = nullptr;

            temp = temp->nextLevel;
      }
      firstLevel = lastLevel = currentLevel = nullptr;
}
