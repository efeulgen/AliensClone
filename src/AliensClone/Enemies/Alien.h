
#ifndef ALIEN_H
#define ALIEN_H

#include <cstdlib>
#include "../../Engine/GameObject.h"
#include "../../Engine/Level.h"
#include "../Player.h"
#include "../Projectile.h"

const double ALIENSPEED = 350.0;
const double ATTACK_RATE = 1.0;

enum AlienAnimState
{
      AAS_Walking,
      AAS_Attacking,
      AAS_Idle,
      AAS_Death
};

class Alien : public GameObject
{
private:
      Player *refToPlayer;
      Level *refToCurrentLevel;
      double attackCounter = 0.0;
      double attackRange = 150.0;

      // animations
      AlienAnimState animState;

      bool isRenderingBloodSplash = false;
      double bloodSplashAnimIndex = 0.0;
      glm::vec2 hitPos = glm::vec2(0.0, 0.0);
      const char *alienBloodSplashSpritesheet[4] = {"./assets/sprites/Enemies/Alien/Alien_bloodSplash_1.png", "./assets/sprites/Enemies/Alien/Alien_bloodSplash_2.png", "./assets/sprites/Enemies/Alien/Alien_bloodSplash_3.png", "./assets/sprites/Enemies/Alien/Alien_bloodSplash_4.png"};

      double walkAnimIndex = 0.0;
      const char *alienWalkingSpritesheet[4] = {"./assets/sprites/Enemies/Alien/AlienWalkAnim/Alien_walk_1.png", "./assets/sprites/Enemies/Alien/AlienWalkAnim/Alien_walk_2.png", "./assets/sprites/Enemies/Alien/AlienWalkAnim/Alien_walk_3.png", "./assets/sprites/Enemies/Alien/AlienWalkAnim/Alien_walk_4.png"};

      double attackingAnimIndex = 0.0;
      const char *alienAttackingSpritesheet[5] = {"./assets/sprites/Enemies/Alien/AlienAttackAnim/Alien_attack_1.png", "./assets/sprites/Enemies/Alien/AlienAttackAnim/Alien_attack_2.png", "./assets/sprites/Enemies/Alien/AlienAttackAnim/Alien_attack_3.png", "./assets/sprites/Enemies/Alien/AlienAttackAnim/Alien_attack_4.png", "./assets/sprites/Enemies/Alien/AlienAttackAnim/Alien_attack_5.png"};

      double deathAnimIndex = 0.0;
      const char *alienDeathSpritesheet[4] = {"./assets/sprites/Enemies/Alien/AlienDeathAnim/Alien_death_1.png", "./assets/sprites/Enemies/Alien/AlienDeathAnim/Alien_death_2.png", "./assets/sprites/Enemies/Alien/AlienDeathAnim/Alien_death_3.png", "./assets/sprites/Enemies/Alien/AlienDeathAnim/Alien_death_4.png"};

      // stats
      int health = 70;

public:
      Alien(glm::vec2 pos, int rSize, Player *playerRef, Level *levelRef);
      ~Alien();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;

      void Attack();
      void GetDamage(int damageAmount);
};

#endif
