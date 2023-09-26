
#include "Mine.h"

Mine::Mine(glm::vec2 pos, int rSize) : GameObject(pos, rSize)
{
      Logger::Logg("Mine Constructor");

      imgFilePath = "";
      gameObjectTag = "Mine";
}

Mine::~Mine()
{
      Logger::Logg("Mine Destructor");
}

void Mine::InitGameObject()
{
}

void Mine::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if (otherObj->GetGameObjectTag() == "Player" && canHurtPlayer)
      {
            static_cast<Player *>(otherObj)->DamagePlayer(damageAmount);
            isRenderingExplosion = true;
            canHurtPlayer = false;
      }
}

void Mine::UpdateGameObject(double deltaTime)
{
      // anims
      if (isRenderingExplosion)
      {
            explosionAnimIndex += deltaTime * 10;
      }
}

void Mine::RenderGameObject(SDL_Renderer *renderer)
{
      GameObject::RenderGameObject(renderer);

      if (isRenderingExplosion)
      {
            RenderAnimation(renderer, explosionSpriteSheet, 128, explosionAnimIndex, transform.position);
            if (static_cast<int>(explosionAnimIndex) >= 3)
            {
                  isRenderingExplosion = false;
                  explosionAnimIndex = 0.0;
                  canBeDestroyed = true;
            }
      }
}
