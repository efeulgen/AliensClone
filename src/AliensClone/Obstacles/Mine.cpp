
#include "Mine.h"

Mine::Mine(glm::vec2 pos, int rSize, Level *refToLev) : GameObject(pos, rSize), refToCurrentLevel{refToLev}
{
      Logger::Logg("Mine Constructor");

      imgFilePath = "./assets/sprites/Obstacles/Mine.png";
      gameObjectTag = "Mine";
}

Mine::~Mine()
{
      Logger::Logg("Mine Destructor");

      refToCurrentLevel = nullptr;
}

void Mine::InitGameObject()
{
}

void Mine::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if ((otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile" || otherObj->GetGameObjectTag() == "Player") && canHurtPlayer)
      {
            static_cast<Player *>(otherObj)->DamagePlayer(damageAmount);
            refToCurrentLevel->GetAudioManager()->PlaySFX(6);
            isRenderingExplosion = true;
            canHurtPlayer = false;
      }
}

void Mine::UpdateGameObject(double deltaTime)
{
      // anims
      if (isRenderingExplosion)
      {
            explosionAnimIndex += deltaTime * 5;
      }
}

void Mine::RenderGameObject(SDL_Renderer *renderer)
{
      GameObject::RenderGameObject(renderer);

      if (isRenderingExplosion)
      {
            RenderAnimation(renderer, explosionSpriteSheet, 4, 256, &explosionAnimIndex, GetRectMidTop() + glm::vec2(-128, -150), true);
            if (static_cast<int>(explosionAnimIndex) >= 3)
            {
                  explosionAnimIndex = 0.0;
                  isRenderingExplosion = false;
                  canBeDestroyed = true;
            }
      }
}
