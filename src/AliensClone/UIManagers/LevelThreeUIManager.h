
#ifndef LEVELTHREEUIMANAGER_H
#define LEVELTHREEUIMANAGER_H

#include "../../Engine/Managers/UIManager.h"

class LevelThreeUIManager : public UIManager
{
public:
      LevelThreeUIManager(int w, int h);
      ~LevelThreeUIManager();

      void RenderUI(SDL_Renderer *renderer) override;
};

#endif
