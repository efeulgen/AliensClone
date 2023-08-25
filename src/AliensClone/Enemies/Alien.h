
#ifndef ALIEN_H
#define ALIEN_H

#include "../../Engine/GameObject.h"

class Alien : public GameObject
{
public:
      Alien();
      ~Alien();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;

      void Attack();
};

#endif
