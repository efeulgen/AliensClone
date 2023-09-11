
#ifndef MAINMENUUIMANAGER_H
#define MAINMENUUIMANAGER_H

#include "../../Engine/Managers/UIManager.h"

class MainMenuUIManager : public UIManager
{
public:
      MainMenuUIManager(int w, int h);
      ~MainMenuUIManager();

      void RenderUI(SDL_Renderer *renderer) override;
};

#endif
