
#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <iostream>
#include <vector>
#include "../Logger/Logger.h"
#include "../Level.h"

struct LevelNode
{
      Level *level;
      LevelNode *nextLevel;
};

class LevelManager
{
private:
      LevelNode *firstLevel = nullptr;
      LevelNode *lastLevel = nullptr;
      LevelNode *currentLevel = nullptr;

public:
      LevelManager();
      ~LevelManager();

      void LoadNextLevel();
      void LoadMainMenu();
      void RestartLevel();
      void AddLevel(Level *level);
      void ClearLevels();

      // *************** getters & setters ******************************
      int GetActiveLevelIndex() const { return currentLevel->level->GetLevelIndex(); }
      Level *GetCurrentLevel() const { return currentLevel->level; }
};

#endif
