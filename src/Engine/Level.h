
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <SDL2/SDL.h>
#include "Logger/Logger.h"
#include "GameObject.h"

class Level
{
protected:
      std::vector<GameObject *> gameObjects;
      bool isLevelComplete;

public:
      Level();
      virtual ~Level();

      virtual void SetupLevel();
      virtual void UpdateLevel(double deltaTime);
      virtual void RenderLevel(SDL_Renderer *renderer);

      // getters & setters
      bool GetIsLevelComplete() const { return isLevelComplete; }
};

#endif
