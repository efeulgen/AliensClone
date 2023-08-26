
#ifndef ALIEN_H
#define ALIEN_H

#include "../../Engine/GameObject.h"

class Alien : public GameObject
{
public:
      Alien(glm::vec2 pos, glm::vec2 vel, int rSize);
      ~Alien();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void CollisionCallback(GameObject *otherObj) override;

      void Attack();
};

#endif
