
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

      if (isBursted)
      {
            burstAnimIndex += deltaTime * 10;
      }
}

void AlienEgg::RenderGameObject(SDL_Renderer *renderer)
{
      if (!isBursted)
      {
            GameObject::RenderGameObject(renderer);
      }
      else
      {
            RenderAnimation(renderer, burstSpriteSheet, 7, rectSize, &burstAnimIndex, transform.position, true);
            if (static_cast<int>(burstAnimIndex) >= 6)
            {
                  burstAnimIndex = 0.0;
                  Alien *newAlien = new Alien(glm::vec2(transform.position.x, transform.position.y), 200, refToPlayer, refToCurrentLevel);
                  newAlien->InitGameObject();
                  refToCurrentLevel->InstantiateGameObject(newAlien);
                  canBeDestroyed = true;
            }
      }
}

void AlienEgg::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if ((otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile") && isHitGround)
      {
            refToCurrentLevel->GetAudioManager()->PlaySFX(4);
            otherObj->SetCanBeDestroyed(true);
            isBursted = true;
      }
}
