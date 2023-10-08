
#include "GooEgg.h"

GooEgg::GooEgg(glm::vec2 pos, int rSize, Player *p, Level *l) : GameObject(pos, rSize), refToPlayer{p}, refToLevel{l}
{
      Logger::Logg("GooEgg Constructor");

      imgFilePath = unexplodedFilePath;
      gameObjectTag = "GooEgg";
}

GooEgg::~GooEgg()
{
      Logger::Logg("GooEgg Destructor");
}

void GooEgg::InitGameObject()
{
}

void GooEgg::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if ((otherObj->GetGameObjectTag() == "Player") && isExploded)
      {
            static_cast<Player *>(otherObj)->SlowDownPlayer();
      }
}

void GooEgg::UpdateGameObject(double deltaTime)
{
      if (refToLevel->GetRefToGameManager()->GetIsGameOver())
      {
            return;
      }

      // anims
      if (isExploding)
      {
            explodeAnimIndex += deltaTime * 5;
      }

      if ((abs(refToPlayer->GetPosition().x - transform.position.x) < 200.0) && !isExploded && !isExploding)
      {
            refToLevel->GetAudioManager()->PlaySFX(4);
            isExploding = true;
      }
}

void GooEgg::RenderGameObject(SDL_Renderer *renderer)
{
      if (!isExploding)
      {
            GameObject::RenderGameObject(renderer);
      }
      else
      {
            RenderAnimation(renderer, explodeSpriteSheet, 3, rectSize, &explodeAnimIndex, transform.position, true, isFlipped);
            if (static_cast<int>(explodeAnimIndex) >= 2)
            {
                  explodeAnimIndex = 0.0;
                  isExploding = false;
                  isExploded = true;
                  imgFilePath = explodedFilePath;
            }
      }
}
