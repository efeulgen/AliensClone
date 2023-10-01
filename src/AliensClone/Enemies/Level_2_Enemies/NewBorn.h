
#ifndef NEWBORN_H
#define NEWBORN_H

#include "../../../Engine/GameObject.h"

class NewBorn : public GameObject
{
public:
      NewBorn(glm::vec2 pos, int rSize);
      ~NewBorn();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
