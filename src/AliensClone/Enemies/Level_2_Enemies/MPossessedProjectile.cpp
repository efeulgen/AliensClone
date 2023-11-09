
#include "MPossessedProjectile.h"

MPossessedProjectile::MPossessedProjectile(glm::vec2 pos, glm::vec2 vel, int rSize, Player *p) : GameObject(pos, vel, rSize), refToPlayer{p}
{
      // Logger::Log("MachinegunPossessedProjectile Constructor");

      imgFilePath = "./assets/sprites/Enemies/MachinegunPossessed/MPossessedProj.png";
      gameObjectTag = "MPossessedProjectile";
}

MPossessedProjectile::~MPossessedProjectile()
{
      // Logger::Log("MachinegunPossessedProjectile Destructor");
}

void MPossessedProjectile::InitGameObject()
{
}

void MPossessedProjectile::UpdateGameObject(double deltaTime)
{
      // bound checking
      if (transform.position.x < 0.0 || transform.position.x > 1500.0 || transform.position.y > 800.0)
      {
            canBeDestroyed = true;
      }

      transform.position.x += velocity.x * deltaTime;
      transform.position.y += velocity.y * deltaTime;
}
void MPossessedProjectile::RenderGameObject(SDL_Renderer *renderer)
{
      GameObject::RenderGameObject(renderer);
}

void MPossessedProjectile::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if (otherObj->GetGameObjectTag() == "Player")
      {
            static_cast<Player *>(otherObj)->DamagePlayer(5);
            canBeDestroyed = true;
      }
}
