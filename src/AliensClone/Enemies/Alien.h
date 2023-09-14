
#ifndef ALIEN_H
#define ALIEN_H

#include <cstdlib>
#include "../../Engine/GameObject.h"
#include "../../Engine/Level.h"
#include "../Player.h"
#include "../Projectile.h"

const double ALIENSPEED = 400.0;
const double ATTACK_RATE = 1.0;

class Alien : public GameObject
{
private:
      Player *refToPlayer;
      Level *refToCurrentLevel;
      double attackCounter = 0.0;
      double attackRange = 150.0;

      // bloodsplash anim
      bool isRenderingBloodSplash;
      double bloodSplashAnimIndex;
      glm::vec2 hitPos;
      const char *alienBloodSplashSpritesheet[4] = {"./assets/sprites/Enemies/Alien/Alien_bloodSplash_1.png", "./assets/sprites/Enemies/Alien/Alien_bloodSplash_2.png", "./assets/sprites/Enemies/Alien/Alien_bloodSplash_3.png", "./assets/sprites/Enemies/Alien/Alien_bloodSplash_4.png"};

      // stats
      int health = 100;

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
