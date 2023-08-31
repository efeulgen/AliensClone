
#ifndef ALIENEGG_H
#define ALIENEGG_H

#include "../../Engine/GameObject.h"

class AlienEgg : public GameObject
{
public:
      AlienEgg(glm::vec2 pos, glm::vec2 vel, int rSize);
      ~AlienEgg();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void CollisionCallback(GameObject *otherObj) override;
};

#endif
