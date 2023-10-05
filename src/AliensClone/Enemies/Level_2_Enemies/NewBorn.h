
#ifndef NEWBORN_H
#define NEWBORN_H

#include <cstdlib>
#include "../../../Engine/GameObject.h"
#include "../../Player.h"
#include "../../../Engine/Level.h"

enum NewBornAnimState
{
      NBAS_Idle,
      NBAS_Crawling,
      NBAS_Attacking
};

class NewBorn : public GameObject
{
private:
      Player *refToPlayer;
      Level *refToLevel;

      double attackRange = 150.0;
      double attackCounter = 0.0;
      double attackRate = 0.75;
      double newBornSpeed = 450.0;

      // animations
      double newBornAnimIndex = 0.0;
      const char *newBornSpriteSheet[4] = {"./assets/sprites/Enemies/NewBorn/NewBorn_1.png", "./assets/sprites/Enemies/NewBorn/NewBorn_2.png", "./assets/sprites/Enemies/NewBorn/NewBorn_3.png", "./assets/sprites/Enemies/NewBorn/NewBorn_4.png"};

      bool isDead = false;
      double newBornDeathAnimIndex = 0.0;
      const char *newBornDeathSpriteSheet[4] = {"./assets/sprites/Enemies/NewBorn/NewBorn_death_1.png", "./assets/sprites/Enemies/NewBorn/NewBorn_death_2.png", "./assets/sprites/Enemies/NewBorn/NewBorn_death_3.png", "./assets/sprites/Enemies/NewBorn/NewBorn_death_4.png"};

public:
      NewBorn(glm::vec2 pos, int rSize, Player *p, Level *l);
      ~NewBorn();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;

      void Attack();
};

#endif
