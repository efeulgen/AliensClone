
#include "AlienEgg.h"

AlienEgg::AlienEgg(glm::vec2 pos, glm::vec2 vel, int rSize, Level *l, Player *p) : GameObject(pos, vel, rSize), refToCurrentLevel{l}, refToPlayer{p}
{
      Logger::Logg("AlienEgg Constructor");

      imgFilePath = "./assets/sprites/Enemies/AlienEgg/AlienEgg_1.png";
      gameObjectTag = "AlienEgg";
}

AlienEgg::~AlienEgg()
{
      Logger::Logg("AlienEgg Destructor");

      refToCurrentLevel = nullptr;
      refToPlayer = nullptr;
}

void AlienEgg::InitGameObject()
{
      srand(refToCurrentLevel->GetSpawnManager()->IncrementSpawnSeed());
      stopPos = 550.0 + static_cast<double>(rand() % 200);
}

void AlienEgg::UpdateGameObject(double deltaTime)
{
      transform.position.x += velocity.x * deltaTime;
      transform.position.y += velocity.y * deltaTime;

      if (transform.position.y >= stopPos)
      {
            isHitGround = true;
            velocity = glm::vec2(0.0, 0.0);
      }
}

void AlienEgg::CollisionCallback(GameObject *otherObj)
{
      if ((otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile") && isHitGround)
      {
            refToCurrentLevel->GetAudioManager()->PlaySFX(4);
            refToCurrentLevel->InstantiateGameObject(new Alien(glm::vec2(transform.position.x, transform.position.y), 200, refToPlayer, refToCurrentLevel));
            canBeDestroyed = true;
            otherObj->SetCanBeDestroyed(true);
      }
}
