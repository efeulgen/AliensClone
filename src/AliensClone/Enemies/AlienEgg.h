
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

      bool isBursted = false;
      double burstAnimIndex = 0.0;
      const char *burstSpriteSheet[5] = {"./assets/sprites/Enemies/AlienEgg/AlienEgg_burst_1.png", "./assets/sprites/Enemies/AlienEgg/AlienEgg_burst_2.png", "./assets/sprites/Enemies/AlienEgg/AlienEgg_burst_3.png", "./assets/sprites/Enemies/AlienEgg/AlienEgg_burst_4.png", "./assets/sprites/Enemies/AlienEgg/AlienEgg_burst_5.png"};

public:
      AlienEgg(glm::vec2 pos, glm::vec2 vel, int rSize, Level *l, Player *p);
      ~AlienEgg();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
