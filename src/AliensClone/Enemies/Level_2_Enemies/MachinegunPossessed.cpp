
#include "MachinegunPossessed.h"

MachinegunPossessed::MachinegunPossessed(glm::vec2 pos, int rSize, Player *p, Level *l) : GameObject(pos, rSize), refToPlayer{p}, refToCurrentLevel{l}
{
      Logger::Logg("MachinegunPossessed Constructor");

      imgFilePath = "./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_mid.png"; // for debug
      gameObjectTag = "MachinegunPossessed";
}

MachinegunPossessed::~MachinegunPossessed()
{
      Logger::Logg("MachinegunPossessed Destrcutor");

      refToPlayer = nullptr;
      refToCurrentLevel = nullptr;
}

void MachinegunPossessed::InitGameObject()
{
      animState = MachinegunPossessedAnimState::MPAS_Searching;
}

void MachinegunPossessed::UpdateGameObject(double deltaTime)
{
      if (refToCurrentLevel->GetRefToGameManager()->GetIsGameOver())
      {
            return;
      }

      // detect player
      double distanceFromPlayer = abs(refToPlayer->GetPosition().x - transform.position.x);
      if (distanceFromPlayer < 700.0 && animState != MachinegunPossessedAnimState::MPAS_Death)
      {
            animState = MachinegunPossessedAnimState::MPAS_Firing;

            fireCounter -= deltaTime;
            if (fireCounter <= 0.0)
            {
                  Fire();
                  fireCounter = FIRE_RATE;
            }

            if (distanceFromPlayer < 250.0)
            {
                  imgFilePath = "./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_mid.png"; // for debug
            }
            else if (refToPlayer->GetPosition().x < transform.position.x)
            {
                  imgFilePath = "./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_left.png"; // for debug
            }
            else if (refToPlayer->GetPosition().x > transform.position.x)
            {
                  imgFilePath = "./assets/sprites/Enemies/MachinegunPossessed/MachinegunPossessed_right.png"; // for debug
            }
      }
      else
      {
            animState = MachinegunPossessedAnimState::MPAS_Searching;
      }
}

void MachinegunPossessed::RenderGameObject(SDL_Renderer *renderer)
{
      GameObject::RenderGameObject(renderer); // for debug

      switch (animState)
      {
      case MachinegunPossessedAnimState::MPAS_Searching:
            // Render searching anim
            break;
      case MachinegunPossessedAnimState::MPAS_Firing:
            // Render firing anim
            break;
      case MachinegunPossessedAnimState::MPAS_Death:
            // Render death anim
            break;
      default:
            break;
      }
}

void MachinegunPossessed::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if (otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile")
      {
            GetDamage(static_cast<Projectile *>(otherObj)->GetDamageAmount());
            otherObj->SetCanBeDestroyed(true);
      }
}

void MachinegunPossessed::GetDamage(double amount)
{
      health -= amount;
      if (health <= 0)
      {
            animState = MachinegunPossessedAnimState::MPAS_Death;
      }
}

void MachinegunPossessed::Fire()
{
      glm::vec2 initPoint = transform.position;
      glm::vec2 initVelocity = glm::normalize(refToPlayer->GetRectMidTop() - initPoint);
      initVelocity.x *= 500.0;
      initVelocity.y *= 500.0;
      refToCurrentLevel->InstantiateGameObject(new MPossessedProjectile(initPoint, initVelocity, 12, refToPlayer));
}
