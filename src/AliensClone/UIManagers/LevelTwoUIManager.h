
#ifndef LEVELTWOUIMANAGER_H
#define LEVELTWOUIMANAGER_H

#include "../../Engine/Managers/UIManager.h"

class LevelTwoUIManager : public UIManager
{
public:
      LevelTwoUIManager(int w, int h);
      ~LevelTwoUIManager();

      void RenderUI(SDL_Renderer *renderer) override;
};

#endif
