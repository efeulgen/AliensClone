
#ifndef ALIENEGG_H
#define ALIENEGG_H

#include "../../Engine/GameObject.h"
#include "../../Engine/Level.h"
#include "../Player.h"
#include "../Enemies/Alien.h"

class AlienEgg : public GameObject
{
private:
      Level *refToCurrentLevel = nullptr;
      Player *refToPlayer = nullptr;
      double stopPos = 0.0;

      bool isHitGround = false;

public:
      AlienEgg(glm::vec2 pos, glm::vec2 vel, int rSize, Level *l, Player *p);
      ~AlienEgg();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void CollisionCallback(GameObject *otherObj) override;
};

#endif
