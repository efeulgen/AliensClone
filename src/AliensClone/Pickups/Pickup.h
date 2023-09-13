
#ifndef PICKUP_H
#define PICKUP_H

#include "../../Engine/GameObject.h"
#include "../Player.h"

enum PickupType
{
      PT_HealthPickup,
      PT_LaserBlasterAmmoPickup,
      PT_FlamethrowerAmmoPickup,
      PT_TrippleShotAmmoPickup
};

class Pickup : public GameObject
{
private:
      PickupType pickupType;

public:
      Pickup(glm::vec2 pos, int rSize, PickupType t);
      ~Pickup();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
