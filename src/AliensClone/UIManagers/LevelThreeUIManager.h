
#ifndef LEVELTHREEUIMANAGER_H
#define LEVELTHREEUIMANAGER_H

#include "../../Engine/Managers/UIManager.h"
#include "../../Engine/Managers/GameManager.h"
#include "../Player.h"

class LevelThreeUIManager : public UIManager
{
private:
      Player *refToPlayer = nullptr;
      GameManager *refToGameManager = nullptr;

public:
      LevelThreeUIManager(int w, int h, Player *p, GameManager *gm);
      ~LevelThreeUIManager();

      void RenderUI(SDL_Renderer *renderer) override;
};

#endif
