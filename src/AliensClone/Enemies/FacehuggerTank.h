
#ifndef FACEHUGGERTANK_H
#define FACEHUGGERTANK_H

#include "../../Engine/GameObject.h"
#include "../../Engine/Level.h"
#include "../Player.h"
#include "Facehugger.h"

class FacehuggerTank : public GameObject
{
private:
      Player *refToPlayer = nullptr;
      Level *refToLevel = nullptr;

      bool isDamaged = false;
      double undamagedTankAnimIndex = 0.0;
      const char *undamagedTankSpriteSheet[4] = {"./assets/sprites/Enemies/Facehugger/FacehuggerTank_Undamaged_1.png", "./assets/sprites/Enemies/Facehugger/FacehuggerTank_Undamaged_2.png", "./assets/sprites/Enemies/Facehugger/FacehuggerTank_Undamaged_3.png", "./assets/sprites/Enemies/Facehugger/FacehuggerTank_Undamaged_4.png"};

      int breakOffsetSeed = 0;
      bool isPassedByPlayer = false;

public:
      FacehuggerTank(glm::vec2 pos, int rSize, Player *player, Level *level);
      ~FacehuggerTank();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
