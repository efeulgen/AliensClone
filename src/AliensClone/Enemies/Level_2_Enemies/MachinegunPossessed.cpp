
#include "MachinegunPossessed.h"

MachinegunPossessed::MachinegunPossessed(glm::vec2 pos, int rSize, Player *p, Level *l) : GameObject(pos, rSize), refToPlayer{p}, refToCurrentLevel{l}
{
      Logger::Log("MachinegunPossessed Constructor");

      gameObjectTag = "MachinegunPossessed";
      renderPriority = 2;
      firingSpriteSheet = leftFiringSpriteSheet;
      deathSpriteSheet = leftDeathSpriteSheet;
}

MachinegunPossessed::~MachinegunPossessed()
{
      Logger::Log("MachinegunPossessed Destrcutor");

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

      switch (animState)
      {
      case MachinegunPossessedAnimState::MPAS_Searching:
            searchingAnimIndex += deltaTime * 2;
            break;
      case MachinegunPossessedAnimState::MPAS_Firing:
            firingAnimIndex += deltaTime * 8;
            break;
      case MachinegunPossessedAnimState::MPAS_Death:
            deathAnimIndex += deltaTime * 8;
            break;
      default:
            break;
      }
      if (isRenderingMuzzleFlash)
      {
            muzzleFlashAnimIndex += deltaTime * 10;
      }

      // detect player
      double distanceFromPlayer = abs(refToPlayer->GetPosition().x - transform.position.x);
      if (distanceFromPlayer < 600.0 && animState != MachinegunPossessedAnimState::MPAS_Death)
      {
            animState = MachinegunPossessedAnimState::MPAS_Firing;

            fireCounter -= deltaTime;
            if (fireCounter <= 0.0)
            {
                  Fire();
                  fireCounter = FIRE_RATE;
            }

            if (distanceFromPlayer < 150.0)
            {
                  firingSpriteSheet = midFiringSpriteSheet;
                  deathSpriteSheet = midDeathSpriteSheet;
                  fireOffset = glm::vec2(65.0, 190.0);
            }
            else if (refToPlayer->GetPosition().x < transform.position.x && distanceFromPlayer < 350.0)
            {
                  firingSpriteSheet = midLeftFiringSpriteSheet;
                  deathSpriteSheet = midLeftDeathSpriteSheet;
                  fireOffset = glm::vec2(30.0, 175.0);
            }
            else if (refToPlayer->GetPosition().x > transform.position.x && distanceFromPlayer < 350.0)
            {
                  firingSpriteSheet = midRightFiringSpriteSheet;
                  deathSpriteSheet = midRightDeathSpriteSheet;
                  fireOffset = glm::vec2(160.0, 160.0);
            }
            else if (refToPlayer->GetPosition().x < transform.position.x)
            {
                  firingSpriteSheet = leftFiringSpriteSheet;
                  deathSpriteSheet = leftDeathSpriteSheet;
                  fireOffset = glm::vec2(-10.0, 130.0);
            }
            else if (refToPlayer->GetPosition().x > transform.position.x)
            {
                  firingSpriteSheet = rightFiringSpriteSheet;
                  deathSpriteSheet = rightDeathSpriteSheet;
                  fireOffset = glm::vec2(200.0, 125.0);
            }
      }
      else
      {
            animState = MachinegunPossessedAnimState::MPAS_Searching;
      }
}

void MachinegunPossessed::RenderGameObject(SDL_Renderer *renderer)
{
      CalculateRect();
      switch (animState)
      {
      case MachinegunPossessedAnimState::MPAS_Searching:
            RenderAnimation(renderer, searchingSpriteSheet, 8, rectSize, &searchingAnimIndex, transform.position, false, isFlipped);
            break;
      case MachinegunPossessedAnimState::MPAS_Firing:
            RenderAnimation(renderer, firingSpriteSheet, 3, rectSize, &firingAnimIndex, transform.position, false, isFlipped);
            break;
      case MachinegunPossessedAnimState::MPAS_Death:
            canBeDestroyed = true; // TODO : for testing delete later
            // Render death animation
            /*
            RenderAnimation(renderer, deathSpriteSheet, 5, rectSize, &deathAnimIndex, transform.position, false, isFlipped);
            if (static_cast<int>(deathAnimIndex) >= 4)
            {
                  deathAnimIndex = 0.0;
                  canBeDestroyed = true;
            }
            */
            break;
      default:
            break;
      }
      if (isRenderingMuzzleFlash)
      {
            RenderAnimation(renderer, muzzleFlashSpritesheet, 3, muzzleFlashRectSize, &muzzleFlashAnimIndex, transform.position + fireOffset, true, false);
            if (static_cast<int>(muzzleFlashAnimIndex) >= 2)
            {
                  muzzleFlashAnimIndex = 0.0;
                  isRenderingMuzzleFlash = false;
            }
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
      glm::vec2 firePos = transform.position + fireOffset + glm::vec2(muzzleFlashRectSize / 2, muzzleFlashRectSize / 2);
      glm::vec2 initVelocity = glm::normalize(refToPlayer->GetRectMidTop() - firePos);
      initVelocity.x *= 700.0;
      initVelocity.y *= 700.0;
      refToCurrentLevel->InstantiateGameObject(new MPossessedProjectile(firePos, initVelocity, 12));
      isRenderingMuzzleFlash = true;
}
