
#ifndef MINE_H
#define MINE_H

#include "../Engine/GameObject.h"
#include "Player.h"

class Mine : public GameObject
{
private:
      int damageAmount = 35;
      bool canHurtPlayer = true;

      // explosion animation
      bool isRenderingExplosion = false;
      double explosionAnimIndex = 0.0;
      const char *explosionSpriteSheet[4] = {"./assets/sprites/Explosion/Explosion_1.png", "./assets/sprites/Explosion/Explosion_2.png", "./assets/sprites/Explosion/Explosion_3.png", "./assets/sprites/Explosion/Explosion_4.png"};

public:
      Mine(glm::vec2 pos, int rSize);
      ~Mine();

      void InitGameObject() override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
};

#endif
