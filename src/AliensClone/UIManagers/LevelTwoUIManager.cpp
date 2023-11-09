
#include "LevelTwoUIManager.h"

LevelTwoUIManager::LevelTwoUIManager(int w, int h, Player *p, GameManager *gm) : UIManager(w, h), refToPlayer{p}, refToGameManager{gm}
{
      Logger::Log("LevelTwoUIManager Constructor");
}

LevelTwoUIManager::~LevelTwoUIManager()
{
      Logger::Log("LevelTwoUIManager Destructor");

      refToPlayer = nullptr;
      refToGameManager = nullptr;
}

void LevelTwoUIManager::RenderUI(SDL_Renderer *renderer)
{
      int playerHealth;
      int playerAmmo;
      if (refToGameManager->GetIsGameOver())
      {
            playerHealth = 0;
            playerAmmo = 0;
            refToPlayer = nullptr;
      }
      else
      {
            playerHealth = refToPlayer->GetHealth();
            playerAmmo = refToPlayer->GetAmmo();
      }

      RenderText(renderer, "Health : " + std::to_string(playerHealth), 255, 0, 0, glm::vec2(52, 52));
      RenderText(renderer, "Health : " + std::to_string(playerHealth), 255, 255, 255, glm::vec2(50, 50));

      RenderText(renderer, "Ammo : " + std::to_string(playerAmmo), 255, 0, 0, glm::vec2(52, 102));
      RenderText(renderer, "Ammo : " + std::to_string(playerAmmo), 255, 255, 255, glm::vec2(50, 100));
}