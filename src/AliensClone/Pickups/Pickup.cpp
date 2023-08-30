
#include "Pickup.h"

Pickup::Pickup(glm::vec2 pos, int rSize, PickupType t) : GameObject(pos, rSize), pickupType{t}
{
      switch (pickupType)
      {
      case PickupType::PT_HealthPickup:
            imgFilePath = "./assets/sprites/Pickups/HealthPickup.png";
            break;
      case PickupType::PT_LaserBlasterAmmoPickup:
            imgFilePath = "./assets/sprites/Pickups/LaserBlasterAmmoPickup.png";
            break;
      case PickupType::PT_FlamethrowerAmmoPickup:
            imgFilePath = "./assets/sprites/Pickups/FlamethrowerAmmoPickup.png";
            break;
      case PickupType::PT_TrippleShotAmmoPickup:
            imgFilePath = "./assets/sprites/Pickups/TrippleShotAmmoPickup.png";
            break;
      default:
            break;
      }
}

Pickup::~Pickup()
{
}

void Pickup::InitGameObject()
{
}

void Pickup::UpdateGameObject(double deltaTime)
{
}

void Pickup::CollisionCallback(GameObject *otherObj)
{
      if (otherObj->GetGameObjectTag() == "Player")
      {
            std::cout << "Pickup is collected." << std::endl;

            switch (pickupType)
            {
            case PickupType::PT_HealthPickup:
                  static_cast<Player *>(otherObj)->HealPlayer();
                  break;
            case PickupType::PT_LaserBlasterAmmoPickup:
                  static_cast<Player *>(otherObj)->IncreaseLaserBlasterAmmo();
                  break;
            case PickupType::PT_FlamethrowerAmmoPickup:
                  static_cast<Player *>(otherObj)->IncreaseFlamethrowerAmmo();
                  break;
            case PickupType::PT_TrippleShotAmmoPickup:
                  static_cast<Player *>(otherObj)->IncreaseTrippleShotAmmo();

            default:
                  break;
            }

            canBeDestroyed = true;
      }
}