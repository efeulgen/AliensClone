
#include "Blob.h"

Blob::Blob(glm::vec2 pos, glm::vec2 vel, int rSize, Player *p, Level *l) : GameObject(pos, vel, rSize), refToPlayer{p}, refToCurrentLevel{l}
{
      Logger::Log("Blob Constructor");

      imgFilePath = "./assets/sprites/Enemies/Blob/Blob.png";
      gameObjectTag = "Blob";
      animState = BlobAnimState::BAS_Blobbing;
}

Blob::~Blob()
{
      Logger::Log("Blob Destructor");

      refToPlayer = nullptr;
      refToCurrentLevel = nullptr;
}

void Blob::InitGameObject()
{
}

void Blob::UpdateGameObject(double deltaTime)
{
      if (refToCurrentLevel->GetRefToGameManager()->GetIsGameOver())
            return;

      // animations
      switch (animState)
      {
      case BlobAnimState::BAS_Blobbing:
            blobbingAnimIndex += deltaTime * 8;
            break;
      case BlobAnimState::BAS_Dissolving:
            dissolvingAnimIndex += deltaTime * 8;
            break;
      default:
            break;
      }

      // sounds
      if (animState == BlobAnimState::BAS_Blobbing)
      {
            if (abs(refToPlayer->GetPosition().x - transform.position.x) < 1000.0)
            {
                  refToCurrentLevel->GetAudioManager()->PlaySFX(14);
            }
            else
            {
                  refToCurrentLevel->GetAudioManager()->StopSFX(14);
            }
      }

      // detect player
      if ((abs(refToPlayer->GetPosition().x - transform.position.x) < 100.0) && (animState == BlobAnimState::BAS_Blobbing))
      {
            refToCurrentLevel->GetAudioManager()->PlaySFX(15);
            animState = BlobAnimState::BAS_Dropping;
            velocity = glm::vec2(0, 10);
      }

      // gravity
      if (animState == BlobAnimState::BAS_Dropping)
      {
            velocity.y += (deltaTime * 3000);
      }

      // death
      if (transform.position.y > refToPlayer->GetRectMidBottom().y)
      {
            animState = BlobAnimState::BAS_Dissolving;
      }

      transform.position.x += velocity.x * deltaTime;
      transform.position.y += velocity.y * deltaTime;
}

void Blob::RenderGameObject(SDL_Renderer *renderer)
{
      switch (animState)
      {
      case BlobAnimState::BAS_Blobbing:
            RenderAnimation(renderer, blobbingSpriteSheet, 4, rectSize, &blobbingAnimIndex, transform.position, false, isFlipped);
            break;
      case BlobAnimState::BAS_Dropping:
            GameObject::RenderGameObject(renderer);
            break;
      case BlobAnimState::BAS_Dissolving:
            RenderAnimation(renderer, dissolvingSpriteSheet, 4, rectSize, &dissolvingAnimIndex, transform.position, true, isFlipped);
            if (static_cast<int>(dissolvingAnimIndex) >= 3)
            {
                  dissolvingAnimIndex = 0.0;
                  canBeDestroyed = true;
            }
            break;
      default:
            break;
      }
}

void Blob::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if ((otherObj->GetGameObjectTag() == "Player") && (animState == BlobAnimState::BAS_Dropping))
      {
            velocity = glm::vec2(0, 0);
            static_cast<Player *>(otherObj)->DamagePlayer(15);
            animState = BlobAnimState::BAS_Dissolving;
      }
}
