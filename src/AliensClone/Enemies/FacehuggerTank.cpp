
#include "FacehuggerTank.h"

FacehuggerTank::FacehuggerTank(glm::vec2 pos, int rSize, Player *player, Level *level) : GameObject(pos, rSize), refToPlayer{player}, refToLevel{level}
{
      Logger::Logg("FacehuggerTank Constructor");

      imgFilePath = "./assets/sprites/Enemies/Facehugger/FacehuggerTank_Damaged.png";
      gameObjectTag = "FacehuggerTank";
}

FacehuggerTank::~FacehuggerTank()
{
      Logger::Logg("FacehuggerTank Destructor");

      refToPlayer = nullptr;
      refToLevel = nullptr;
}

void FacehuggerTank::InitGameObject()
{
}

void FacehuggerTank::UpdateGameObject(double deltaTime)
{
      if (refToPlayer->GetPosition().x >= transform.position.x + 200.0)
      {
            // spawn facehugger
            isDamaged = true;
      }

      if (!isDamaged)
      {
            undamagedTankAnimIndex += deltaTime * 8;
      }
}

void FacehuggerTank::RenderGameObject(SDL_Renderer *renderer)
{
      if (isDamaged)
      {
            GameObject::RenderGameObject(renderer);
      }
      else
      {
            CalculateRect();
            RenderAnimation(renderer, undamagedTankSpriteSheet, 4, rectSize, &undamagedTankAnimIndex, transform.position, false);
      }
}

void FacehuggerTank::CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect)
{
      if (otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile")
      {
            otherObj->SetCanBeDestroyed(true);
            isDamaged = true;
            refToLevel->GetAudioManager()->PlaySFX(7);
      }
}
