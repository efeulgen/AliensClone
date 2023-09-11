
#ifndef LEVELONEUIMANAGER_H
#define LEVELONEUIMANAGER_H

#include "../../Engine/Managers/UIManager.h"
#include "../../Engine/Managers/GameManager.h"
#include "../Player.h"

class LevelOneUIManager : public UIManager
{
private:
      Player *refToPlayer = nullptr;
      GameManager *refToGameManager = nullptr;

public:
      LevelOneUIManager(int w, int h, Player *p, GameManager *gm);
      ~LevelOneUIManager();

      void RenderUI(SDL_Renderer *renderer) override;
};

#endif
