
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

      double searchingAnimIndex = 0.0;
      const char *searchingSpriteSheet[8] = {"./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_right.png", "./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_mid_right.png", "./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_mid.png", "./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_mid_left.png", "./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_left.png", "./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_mid_left.png", "./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_mid.png", "./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_mid_right.png"};

      double firingAnimIndex = 0.0;
      const char **firingSpriteSheet;
      const char *rightFiringSpriteSheet[3] = {"./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_rightFiring_1.png", "./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_rightFiring_2.png", "./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_rightFiring_3.png"};
      const char *midRightFiringSpriteSheet[3] = {"./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_midRightFiring_1.png", "./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_midRightFiring_2.png", "./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_midRightFiring_3.png"};
      const char *midFiringSpriteSheet[3] = {"./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_midFiring_1.png", "./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_midFiring_2.png", "./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_midFiring_3.png"};
      const char *midLeftFiringSpriteSheet[3] = {"./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_midLeftFiring_1.png", "./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_midLeftFiring_2.png", "./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_midLeftFiring_3.png"};
      const char *leftFiringSpriteSheet[3] = {"./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_leftFiring_1.png", "./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_leftFiring_2.png", "./assets/sprites/Enemies/MachinegunPossessed/Firing/MachinegunPossessed_leftFiring_3.png"};

      double deathAnimIndex = 0.0;

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
