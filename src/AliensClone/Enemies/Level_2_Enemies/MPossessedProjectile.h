
#ifndef MPOSSESSEDPROJECTILE_H
#define MPOSSESSEDPROJECTILE_H

#include "../../../Engine/GameObject.h"
#include "../../Player.h"

class MPossessedProjectile : public GameObject
{
public:
      MPossessedProjectile(glm::vec2 pos, glm::vec2 vel, int rSize);
      ~MPossessedProjectile();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
