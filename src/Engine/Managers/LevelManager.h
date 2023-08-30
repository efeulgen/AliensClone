
#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <iostream>
#include <vector>
#include "../Logger/Logger.h"
#include "../Level.h"

class LevelManager
{
private:
      std::vector<Level *> levels;
      int activeLevelIndex = 0;

public:
      LevelManager();
      ~LevelManager();

      void LoadNextLevel();
      void LoadMainMenu();
      void RestartLevel();
      void AddLevel(Level *level);
      void ClearLevels();

      // getters & setters
      int GetActiveLevelIndex() const { return activeLevelIndex; }
      Level *GetCurrentLevel() const { return levels[activeLevelIndex]; }
};

#endif
