
#ifndef GOOEGG_H
#define GOOEGG_H

#include <cstdlib>
#include "../../Engine/GameObject.h"
#include "../../Engine/Level.h"
#include "../Player.h"

class GooEgg : public GameObject
{
private:
      Player *refToPlayer;
      Level *refToLevel;

      const char *explodedFilePath = "./assets/sprites/Obstacles/GooEgg_exploded.png";
      const char *unexplodedFilePath = "./assets/sprites/Obstacles/GooEgg_unexploded.png";

      // animations
      double explodeAnimIndex = 0.0;
      const char *explodeSpriteSheet[3] = {"./assets/sprites/Obstacles/GooEgg_explode_1.png", "./assets/sprites/Obstacles/GooEgg_explode_2.png", "./assets/sprites/Obstacles/GooEgg_explode_3.png"};

      bool isExploding = false;
      bool isExploded = false;

public:
      GooEgg(glm::vec2 pos, int rSize, Player *p, Level *l);
      ~GooEgg();

      void InitGameObject() override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
};

#endif
