
#ifndef MPOSSESSEDPROJECTILE_H
#define MPOSSESSEDPROJECTILE_H

#include "../../../Engine/GameObject.h"
#include "../../Player.h"

class MPossessedProjectile : public GameObject
{
private:
      Player *refToPlayer;

public:
      MPossessedProjectile(glm::vec2 pos, glm::vec2 vel, int rSize, Player *p);
      ~MPossessedProjectile();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
