
#ifndef POSSESSED_H
#define POSSESSED_H

#include "../../../Engine/GameObject.h"
#include "../../../Engine/Level.h"
#include "../../Player.h"
#include "../../Projectile.h"

enum PossessedAnimState
{
      POSAS_Walking,
      POSAS_Attack,
      POSAS_Idle
};

class Possessed : public GameObject
{
private:
      Player *refToPlayer;
      Level *refToLevel;

      PossessedAnimState animState;

      double attackRange = 150.0;
      double attackCounter = 0.0;
      double attackRate = 2.75;
      double possessedSpeed = 100.0;

      // stats
      int health = 280;
      bool isDead = false;

      // animations
      double possessedWalkAnimIndex = 0.0;
      const char *possessedWalkSpriteSheet[4] = {"./assets/sprites/Enemies/Possessed/Possessed_walk_1.png", "./assets/sprites/Enemies/Possessed/Possessed_walk_2.png", "./assets/sprites/Enemies/Possessed/Possessed_walk_3.png", "./assets/sprites/Enemies/Possessed/Possessed_walk_4.png"};

      double possessedAttackAnimIndex = 0.0;
      const char *possessedAttackSpriteSheet[4] = {"./assets/sprites/Enemies/Possessed/Possessed_attack_1.png", "./assets/sprites/Enemies/Possessed/Possessed_attack_2.png", "./assets/sprites/Enemies/Possessed/Possessed_attack_3.png", "./assets/sprites/Enemies/Possessed/Possessed_attack_4.png"};

      double possessedDeathAnimIndex = 0.0;
      const char *possessedDeathSpriteSheet[6] = {"./assets/sprites/Enemies/Possessed/Possessed_death_1.png", "./assets/sprites/Enemies/Possessed/Possessed_death_2.png", "./assets/sprites/Enemies/Possessed/Possessed_death_3.png", "./assets/sprites/Enemies/Possessed/Possessed_death_4.png", "./assets/sprites/Enemies/Possessed/Possessed_death_5.png", "./assets/sprites/Enemies/Possessed/Possessed_death_6.png"};

public:
      Possessed(glm::vec2 pos, int rSize, Player *p, Level *l);
      ~Possessed();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;

      void Attack();
      void GetDamage(int amount);
};

#endif
