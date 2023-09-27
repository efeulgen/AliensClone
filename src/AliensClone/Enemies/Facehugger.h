
#ifndef FACEHUGGER_H
#define FACEHUGGER_H

#include <cstdlib>
#include "../../Engine/GameObject.h"
#include "../../Engine/Level.h"
#include "../Player.h"

class Facehugger : public GameObject
{
private:
      double facehuggerSpeed = 400.0;

      Player *refToPlayer = nullptr;
      Level *refToCurrentLevel = nullptr;

public:
      Facehugger(glm::vec2 pos, int rSize, Player *p, Level *l);
      ~Facehugger();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
