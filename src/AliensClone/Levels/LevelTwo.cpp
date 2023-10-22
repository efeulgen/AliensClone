
#include "LevelTwo.h"

LevelTwo::LevelTwo(int index, int w, int h, int len, GameManager *gManager, bool isFinal) : Level(index, w, h, len, gManager, isFinal)
{
      Logger::Logg("LevelTwo Constructor");

      levelBackgroundPath_1 = "./assets/sprites/Background_2_1.png";
      levelBackgroundPath_2 = "./assets/sprites/Background_2_2.png";
      levelBackgroundPath_3 = "./assets/sprites/Background_2_1.png";
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
      audioManager->AddSFX("./audio/splat_1.wav");                       // 13
      audioManager->AddSFX("./audio/slimey_1.wav");                      // 14
      audioManager->AddSFX("./audio/slug_1.wav");                        // 15
      audioManager->AddSFX("./audio/slug_2.wav");                        // 16

      Mix_VolumeChunk(audioManager->GetSFX(1).chunk, 100);
      Mix_VolumeChunk(audioManager->GetSFX(11).chunk, 25);
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
      spawnManager->CreateSpawnObject("Possessed", 8.0);
      spawnManager->CreateSpawnObject("Blob", 7.5);

      uiManager = new LevelTwoUIManager(windowWidth, windowHeight, player, refToGameManager);

      // pickups
      InstantiateGameObject(new Pickup(glm::vec2(800, 650), 128, PickupType::PT_HealthPickup));
      InstantiateGameObject(new Pickup(glm::vec2(1800, 650), 128, PickupType::PT_HealthPickup));
      InstantiateGameObject(new Pickup(glm::vec2(4200, 650), 128, PickupType::PT_HealthPickup));
      InstantiateGameObject(new Pickup(glm::vec2(5500, 600), 128, PickupType::PT_HealthPickup));
      InstantiateGameObject(new Pickup(glm::vec2(7500, 600), 128, PickupType::PT_HealthPickup));

      InstantiateGameObject(new Pickup(glm::vec2(1500, 750), 128, PickupType::PT_LaserBlasterAmmoPickup));
      InstantiateGameObject(new Pickup(glm::vec2(3500, 700), 128, PickupType::PT_LaserBlasterAmmoPickup));
      InstantiateGameObject(new Pickup(glm::vec2(5200, 550), 128, PickupType::PT_LaserBlasterAmmoPickup));
      InstantiateGameObject(new Pickup(glm::vec2(7500, 600), 128, PickupType::PT_LaserBlasterAmmoPickup));

      InstantiateGameObject(new Pickup(glm::vec2(2300, 600), 128, PickupType::PT_FlamethrowerAmmoPickup));
      InstantiateGameObject(new Pickup(glm::vec2(4500, 650), 128, PickupType::PT_FlamethrowerAmmoPickup));

      InstantiateGameObject(new Pickup(glm::vec2(1250, 750), 128, PickupType::PT_TrippleShotAmmoPickup));
      InstantiateGameObject(new Pickup(glm::vec2(2800, 650), 128, PickupType::PT_TrippleShotAmmoPickup));

      // machinegun possessed
      for (int i = 1; i < 4; i++)
      {
            if (i % 2 != 0)
            {
                  InstantiateGameObject(new MachinegunPossessed(glm::vec2(2000.0 * i, 150), 256, player, this));
                  InstantiateGameObject(new MachinegunPossessed(glm::vec2(2000.0 * i + 400, 150), 256, player, this));
                  InstantiateGameObject(new MachinegunPossessed(glm::vec2(2000.0 * i + 800, 150), 256, player, this));
            }
      }

      // obstacles
      for (int i = 1; i < 8; i++)
      {
            srand(i * 10);
            int yPosVariance = rand() % 100;
            InstantiateGameObject(new GooEgg(glm::vec2(i * 2000.0, 650.0 + yPosVariance), 128, player, this));
      }

      Level::SetupLevel();
}
