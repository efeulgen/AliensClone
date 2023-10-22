
#ifndef MACHINEGUNPOSSESSED_H
#define MACHINEGUNPOSSESSED_H

#include "../../../Engine/GameObject.h"
#include "../../../Engine/Level.h"
#include "../../Player.h"
#include "MPossessedProjectile.h"

const double FIRE_RATE = 0.75;

enum MachinegunPossessedAnimState
{
      MPAS_Searching,
      MPAS_Firing,
      MPAS_Death
};

class MachinegunPossessed : public GameObject
{
private:
      Player *refToPlayer;
      Level *refToCurrentLevel;

      int health = 90;
      double fireCounter = 0.0;
      glm::vec2 fireOffset = glm::vec2(0.0, 0.0);
      int muzzleFlashRectSize = 64;

      // animations
      MachinegunPossessedAnimState animState;

      bool isRenderingMuzzleFlash = false;
      double muzzleFlashAnimIndex = 0.0;
      const char *muzzleFlashSpritesheet[3] = {"./assets/sprites/FX/MuzzleFlash/MuzzleFlash_1.png", "./assets/sprites/FX/MuzzleFlash/MuzzleFlash_2.png", "./assets/sprites/FX/MuzzleFlash/MuzzleFlash_3.png"};

public:
      MachinegunPossessed(glm::vec2 pos, int rSize, Player *p, Level *l);
      ~MachinegunPossessed();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;

      void GetDamage(double amount);
      void Fire();
};

#endif
