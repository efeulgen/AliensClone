
#ifndef MACHINEGUNPOSSESSED_H
#define MACHINEGUNPOSSESSED_H

#include "../../../Engine/GameObject.h"

class MachinegunPossessed : public GameObject
{
public:
      MachinegunPossessed(glm::vec2 pos, int rSize);
      ~MachinegunPossessed();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
