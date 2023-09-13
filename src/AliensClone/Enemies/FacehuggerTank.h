
#ifndef FACEHUGGERTANK_H
#define FACEHUGGERTANK_H

#include "../../Engine/GameObject.h"
#include "../Player.h"

class FacehuggerTank : public GameObject
{
private:
      Player *refToPlayer;

public:
      FacehuggerTank(glm::vec2 pos, int rSize, Player *player);
      ~FacehuggerTank();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
