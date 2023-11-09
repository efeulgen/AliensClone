
#include "GooEgg.h"

GooEgg::GooEgg(glm::vec2 pos, int rSize, Player *p, Level *l) : GameObject(pos, rSize), refToPlayer{p}, refToLevel{l}
{
      Logger::Log("GooEgg Constructor");

      imgFilePath = "./assets/sprites/Obstacles/GooEgg/GooEgg_unexploded.png";
      gameObjectTag = "GooEgg";
      animState = GooEggAnimState::GEAS_Unexploded;
}

GooEgg::~GooEgg()
{
      Logger::Log("GooEgg Destructor");
}

void GooEgg::InitGameObject()
{
}

void GooEgg::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if ((otherObj->GetGameObjectTag() == "Player"))
      {
            if (animState == GooEggAnimState::GEAS_Exploded)
            {
                  static_cast<Player *>(otherObj)->SlowDownPlayer();
                  animState = GooEggAnimState::GEAS_Infecting;
            }
            else if ((animState == GooEggAnimState::GEAS_Burning) && canDamagePlayer)
            {
                  static_cast<Player *>(otherObj)->DamagePlayer(5);
                  canDamagePlayer = false;
            }
      }
      if (otherObj->GetGameObjectTag() == "FlamethrowerProjectile" && (animState == GooEggAnimState::GEAS_Exploded || animState == GooEggAnimState::GEAS_Infecting))
      {
            animState = GooEggAnimState::GEAS_Burning;
      }
      if (otherObj->GetGameObjectTag() == "LaserBlasterProjectile" && (animState == GooEggAnimState::GEAS_Unexploded))
      {
            GetDamage(1);
            otherObj->SetCanBeDestroyed(true);
            refToLevel->GetAudioManager()->PlaySFX(13);
      }
      if (otherObj->GetGameObjectTag() == "TrippleShotProjectile" && (animState == GooEggAnimState::GEAS_Unexploded))
      {
            GetDamage(3);
            otherObj->SetCanBeDestroyed(true);
            refToLevel->GetAudioManager()->PlaySFX(13);
      }
}

void GooEgg::UpdateGameObject(double deltaTime)
{
      if (refToLevel->GetRefToGameManager()->GetIsGameOver())
      {
            return;
      }

      if (!canDamagePlayer)
      {
            fireDamageCounter += deltaTime;
            if (fireDamageCounter >= fireDamageRate)
            {
                  canDamagePlayer = true;
                  fireDamageCounter = 0.0;
            }
      }

      if (animState == GooEggAnimState::GEAS_Infecting)
      {
            infectingAnimDurationCounter += deltaTime;
            if (infectingAnimDurationCounter >= infectingAnimDuration)
            {
                  animState = GooEggAnimState::GEAS_Exploded;
                  infectingAnimDurationCounter = 0.0;
            }
      }

      // animations
      switch (animState)
      {
      case GooEggAnimState::GEAS_Exploding:
            explodingAnimIndex += deltaTime * 5;
            break;
      case GooEggAnimState::GEAS_Exploded:
            explodedAnimIndex += deltaTime * 5;
            break;
      case GooEggAnimState::GEAS_Infecting:
            infectingAnimIndex += deltaTime * 5;
            break;
      case GooEggAnimState::GEAS_Burning:
            burningAnimIndex += deltaTime * 5;
            break;
      default:
            break;
      }

      // explode on detect player
      if ((abs(refToPlayer->GetPosition().x - transform.position.x) < 200.0) && animState == GooEggAnimState::GEAS_Unexploded)
      {
            refToLevel->GetAudioManager()->PlaySFX(4);
            animState = GooEggAnimState::GEAS_Exploding;
      }
}

void GooEgg::RenderGameObject(SDL_Renderer *renderer)
{
      CalculateRect();
      switch (animState)
      {
      case GooEggAnimState::GEAS_Unexploded:
            GameObject::RenderGameObject(renderer);
            break;
      case GooEggAnimState::GEAS_Exploding:
            RenderAnimation(renderer, explodingSpriteSheet, 3, rectSize, &explodingAnimIndex, transform.position, true, isFlipped);
            if (static_cast<int>(explodingAnimIndex) >= 2)
            {
                  explodingAnimIndex = 0.0;
                  animState = GooEggAnimState::GEAS_Exploded;
            }
            break;
      case GooEggAnimState::GEAS_Exploded:
            RenderAnimation(renderer, explodedSpriteSheet, 3, rectSize, &explodedAnimIndex, transform.position, false, isFlipped);
            break;
      case GooEggAnimState::GEAS_Infecting:
            RenderAnimation(renderer, infectingSpriteSheet, 3, rectSize, &infectingAnimIndex, transform.position, false, isFlipped);
            break;
      case GooEggAnimState::GEAS_Burning:
            RenderAnimation(renderer, burningSpriteSheet, 3, rectSize, &burningAnimIndex, transform.position, false, isFlipped);
            break;
      default:
            break;
      }
}

void GooEgg::GetDamage(int amount)
{
      health -= amount;
      if (health <= 0)
      {
            refToLevel->GetAudioManager()->PlaySFX(4);
            animState = GooEggAnimState::GEAS_Exploding;
      }
}
