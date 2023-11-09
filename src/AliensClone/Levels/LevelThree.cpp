
#include "LevelThree.h"

LevelThree::LevelThree(int index, int w, int h, int len, GameManager *gManager, bool isFinal) : Level(index, w, h, len, gManager, isFinal)
{
      Logger::Log("LevelThree Constructor");

      levelBackgroundPath_1 = "./assets/sprites/Background_3.png";
      levelBackgroundPath_2 = "./assets/sprites/Background_3.png";
      levelBackgroundPath_3 = "./assets/sprites/Background_3.png";
}

LevelThree::~LevelThree()
{
      Logger::Log("LevelThree Destructor");
}

void LevelThree::SetupLevelSounds()
{
      audioManager->AddSFX("./audio/dummy_PlayerLaserBlasterSound.wav"); // 0
      audioManager->AddSFX("./audio/dummy_PlayerFlamethrowerSound.wav"); // 1
      audioManager->AddSFX("./audio/Reload.wav");                        // 2
      audioManager->AddSFX("./audio/OutOfAmmo.wav");                     // 3
      audioManager->AddSFX("./audio/smash.wav");                         // 4
      audioManager->AddSFX("./audio/player_hurt.wav");                   // 5
      audioManager->AddSFX("./audio/Minor_Explosion.wav");               // 6
}

void LevelThree::SetupLevel()
{
      SDL_ShowCursor(0);

      // player
      player = new Player(glm::vec2(300, windowHeight * 2 / 3), glm::vec2(600.0, 600.0), 250, this, windowWidth, windowHeight);
      InstantiateGameObject(player);

      // managers
      spawnManager = new LevelThreeSpawnManager();
      uiManager = new LevelThreeUIManager(windowWidth, windowHeight, player, refToGameManager);

      // pickups

      Level::SetupLevel();
}
