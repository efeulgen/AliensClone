
#include "LevelTwo.h"

LevelTwo::LevelTwo(int index, int w, int h, int len, GameManager *gManager, bool isFinal) : Level(index, w, h, len, gManager, isFinal)
{
      Logger::Logg("LevelTwo Constructor");

      levelBackgroundPath_1 = "./assets/sprites/Background_2.png";
      levelBackgroundPath_2 = "./assets/sprites/Background_2.png";
      levelBackgroundPath_3 = "./assets/sprites/Background_2.png";
}

LevelTwo::~LevelTwo()
{
      Logger::Logg("LevelTwo Destructor");
}

void LevelTwo::SetupLevelSounds()
{
      audioManager->AddSFX("./audio/dummy_PlayerLaserBlasterSound.wav"); // 0
      audioManager->AddSFX("./audio/dummy_PlayerFlamethrowerSound.wav"); // 1
      audioManager->AddSFX("./audio/Reload.wav");                        // 2
      audioManager->AddSFX("./audio/OutOfAmmo.wav");                     // 3
      audioManager->AddSFX("./audio/smash.wav");                         // 4
      audioManager->AddSFX("./audio/player_hurt.wav");                   // 5
      audioManager->AddSFX("./audio/Minor_Explosion.wav");               // 6
      audioManager->AddSFX("./audio/glass_shatter.wav");                 // 7
      audioManager->AddSFX("./audio/gore_sound_1.wav");                  // 8
      audioManager->AddSFX("./audio/bug_scream_sound_1.wav");            // 9
      audioManager->AddSFX("./audio/possessed_death.wav");               // 10
      audioManager->AddSFX("./audio/power_up_1.wav");                    // 11
      audioManager->AddSFX("./audio/possessed_hurt.wav");                // 12
}

void LevelTwo::SetupLevel()
{
      SDL_ShowCursor(0);

      // player
      player = new Player(glm::vec2(300, windowHeight * 2 / 3), glm::vec2(600.0, 600.0), 250, this, windowWidth, windowHeight);
      InstantiateGameObject(player);

      // managers
      spawnManager = new LevelTwoSpawnManager(player, this);
      spawnManager->CreateSpawnObject("NewBorn", 5.0);
      spawnManager->CreateSpawnObject("Possessed", 4.0);

      uiManager = new LevelTwoUIManager(windowWidth, windowHeight, player, refToGameManager);

      // pickups

      Level::SetupLevel();
}
