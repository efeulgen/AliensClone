
#ifndef GOOEGG_H
#define GOOEGG_H

#include <cstdlib>
#include "../../Engine/GameObject.h"
#include "../../Engine/Level.h"
#include "../Player.h"

enum GooEggAnimState
{
      GEAS_Unexploded,
      GEAS_Exploding,
      GEAS_Exploded,
      GEAS_Infecting,
      GEAS_Burning
};

class GooEgg : public GameObject
{
private:
      Player *refToPlayer;
      Level *refToLevel;

      bool canDamagePlayer = true;
      double fireDamageRate = 1.5;
      double fireDamageCounter = 0.0;
      int health = 3;

      // animations
      GooEggAnimState animState;

      double explodingAnimIndex = 0.0;
      const char *explodingSpriteSheet[3] = {"./assets/sprites/Obstacles/GooEgg/GooEgg_exploding_1.png", "./assets/sprites/Obstacles/GooEgg/GooEgg_exploding_2.png", "./assets/sprites/Obstacles/GooEgg/GooEgg_exploding_3.png"};

      double explodedAnimIndex = 0.0;
      const char *explodedSpriteSheet[3] = {"./assets/sprites/Obstacles/GooEgg/GooEgg_exploded_1.png", "./assets/sprites/Obstacles/GooEgg/GooEgg_exploded_2.png", "./assets/sprites/Obstacles/GooEgg/GooEgg_exploded_3.png"};

      double infectingAnimIndex = 0.0;
      const char *infectingSpriteSheet[3] = {"./assets/sprites/Obstacles/GooEgg/GooEgg_infecting_1.png", "./assets/sprites/Obstacles/GooEgg/GooEgg_infecting_2.png", "./assets/sprites/Obstacles/GooEgg/GooEgg_infecting_3.png"};
      double infectingAnimDurationCounter = 0.0;
      double infectingAnimDuration = 4.0;

      double burningAnimIndex = 0.0;
      const char *burningSpriteSheet[3] = {"./assets/sprites/Obstacles/GooEgg/GooEgg_burning_1.png", "./assets/sprites/Obstacles/GooEgg/GooEgg_burning_2.png", "./assets/sprites/Obstacles/GooEgg/GooEgg_burning_3.png"};

public:
      GooEgg(glm::vec2 pos, int rSize, Player *p, Level *l);
      ~GooEgg();

      void InitGameObject() override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;

      void GetDamage(int amount);
};

#endif
