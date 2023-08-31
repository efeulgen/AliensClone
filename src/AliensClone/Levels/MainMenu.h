
#ifndef MAINMENU_H
#define MAINMENU_H

#include "../../Engine/Level.h"

class MainMenu : public Level
{
public:
      MainMenu(int index, int w, int h, int len, GameManager *gManager, bool isFinal = false);
      ~MainMenu();

      void SetupLevel() override;
      void RenderLevel(SDL_Renderer *renderer) override;
};

#endif
