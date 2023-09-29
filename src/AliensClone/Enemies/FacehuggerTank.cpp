
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
      if (isDamaged || refToLevel->GetRefToGameManager()->GetIsGameOver())
            return;

      breakOffsetSeed++;
      srand(breakOffsetSeed);
      int breakOffset = (rand() % 400) + 250;
      if ((refToPlayer->GetPosition().x >= transform.position.x + breakOffset) && !isPassedByPlayer)
      {
            isPassedByPlayer = true;
            int breakChance = rand() % 2;
            if (breakChance == 1)
            {
                  refToLevel->GetAudioManager()->PlaySFX(7);
                  refToLevel->GetAudioManager()->PlaySFX(8);
                  refToLevel->InstantiateGameObject(new Facehugger(transform.position + glm::vec2(0.0, 200.0), 128, refToPlayer, refToLevel));
                  isDamaged = true;
            }
      }

      undamagedTankAnimIndex += deltaTime * 8;
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
      if ((otherObj->GetGameObjectTag() == "LaserBlasterProjectile" || otherObj->GetGameObjectTag() == "FlamethrowerProjectile" || otherObj->GetGameObjectTag() == "TrippleShotProjectile") && !isDamaged)
      {
            otherObj->SetCanBeDestroyed(true);
            refToLevel->GetAudioManager()->PlaySFX(7);
            refToLevel->GetAudioManager()->PlaySFX(8);
            refToLevel->InstantiateGameObject(new Facehugger(transform.position + glm::vec2(0.0, 200.0), 128, refToPlayer, refToLevel));
            isDamaged = true;
      }
}
