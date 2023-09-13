
#ifndef FACEHUGGER_H
#define FACEHUGGER_H

#include "../../Engine/GameObject.h"

class Facehugger : public GameObject
{
public:
      Facehugger(glm::vec2 pos, glm::vec2 vel, int rSize);
      ~Facehugger();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
