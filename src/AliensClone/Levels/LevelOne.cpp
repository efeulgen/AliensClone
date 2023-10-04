
#include "LevelOne.h"

LevelOne::LevelOne(int index, int w, int h, int len, GameManager *gManager, bool isFinal) : Level(index, w, h, len, gManager, isFinal)
{
      Logger::Logg("LevelOne Constructor");

      levelBackgroundPath_1 = "./assets/sprites/Background_1_1.png";
      levelBackgroundPath_2 = "./assets/sprites/Background_1_2.png";
      levelBackgroundPath_3 = "./assets/sprites/Background_1_1.png";
}

LevelOne::~LevelOne()
{
      Logger::Logg("LevelOne Destructor");
}

void LevelOne::SetupLevelSounds()
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
      audioManager->AddSFX("./audio/alien_scream_1.wav");                // 10
      audioManager->AddSFX("./audio/power_up_1.wav");                    // 11

      Mix_VolumeChunk(audioManager->GetSFX(1).chunk, 100);
      Mix_VolumeChunk(audioManager->GetSFX(11).chunk, 25);
}

void LevelOne::SetupLevel()
{
      SDL_ShowCursor(0);

      // player
      player = new Player(glm::vec2(300, windowHeight * 2 / 3), glm::vec2(600.0, 600.0), 250, this, windowWidth, windowHeight);

      // facehugger tanks
      for (int i = 1; i < 8; i++)
      {
            InstantiateGameObject(new FacehuggerTank(glm::vec2(i * 2000.0, 410), 256, i * 5, player, this));
            InstantiateGameObject(new FacehuggerTank(glm::vec2(i * 2000.0 + 200, 410), 256, (i + 1) * 5, player, this));
            InstantiateGameObject(new FacehuggerTank(glm::vec2(i * 2000.0 + 400, 410), 256, (i + 2) * 5, player, this));
      }

      InstantiateGameObject(player); // create render layers

      // managers
      spawnManager = new LevelOneSpawnManager(player, this);
      spawnManager->CreateSpawnObject("Alien", 5.0);
      spawnManager->CreateSpawnObject("AlienEgg", 7.5);
      spawnManager->CreateSpawnObject("Facehugger", 3.0); // 8.5

      uiManager = new LevelOneUIManager(windowWidth, windowHeight, player, refToGameManager);

      // pickups
      InstantiateGameObject(new Pickup(glm::vec2(800, 600), 128, PickupType::PT_HealthPickup));
      InstantiateGameObject(new Pickup(glm::vec2(1700, 600), 128, PickupType::PT_HealthPickup));
      InstantiateGameObject(new Pickup(glm::vec2(3700, 600), 128, PickupType::PT_HealthPickup));
      InstantiateGameObject(new Pickup(glm::vec2(5000, 600), 128, PickupType::PT_HealthPickup));
      InstantiateGameObject(new Pickup(glm::vec2(7500, 600), 128, PickupType::PT_HealthPickup));
      InstantiateGameObject(new Pickup(glm::vec2(1200, 600), 128, PickupType::PT_LaserBlasterAmmoPickup));
      InstantiateGameObject(new Pickup(glm::vec2(3200, 600), 128, PickupType::PT_LaserBlasterAmmoPickup));
      InstantiateGameObject(new Pickup(glm::vec2(6500, 600), 128, PickupType::PT_LaserBlasterAmmoPickup));
      InstantiateGameObject(new Pickup(glm::vec2(2300, 600), 128, PickupType::PT_FlamethrowerAmmoPickup));
      InstantiateGameObject(new Pickup(glm::vec2(2800, 600), 128, PickupType::PT_TrippleShotAmmoPickup));

      // obstacles
      for (int i = 1; i < 8; i++)
      {
            srand(i * 10);
            int yPosVariance = rand() % 100;
            InstantiateGameObject(new Mine(glm::vec2(i * 2000.0, 700.0 + yPosVariance), 64, this));
      }

      Level::SetupLevel();
}
