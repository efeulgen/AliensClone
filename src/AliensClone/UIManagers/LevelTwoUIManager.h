
#ifndef LEVELTWOUIMANAGER_H
#define LEVELTWOUIMANAGER_H

#include "../../Engine/Managers/UIManager.h"
#include "../../Engine/Managers/GameManager.h"
#include "../Player.h"

class LevelTwoUIManager : public UIManager
{
private:
      Player *refToPlayer = nullptr;
      GameManager *refToGameManager = nullptr;

public:
      LevelTwoUIManager(int w, int h, Player *p, GameManager *gm);
      ~LevelTwoUIManager();

      void RenderUI(SDL_Renderer *renderer) override;
};

#endif
