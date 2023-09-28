
#include "LevelOne.h"

LevelOne::LevelOne(int index, int w, int h, int len, GameManager *gManager, bool isFinal) : Level(index, w, h, len, gManager, isFinal)
{
      Logger::Logg("LevelOne Constructor");

      levelBackgroundPath = "./assets/sprites/Background_1.png";
}

LevelOne::~LevelOne()
{
      Logger::Logg("LevelOne Destructor");
}

void LevelOne::SetupLevelSounds()
{
      audioManager->AddChunk("./audio/dummy_PlayerLaserBlasterSound.wav"); // 0
      audioManager->AddChunk("./audio/dummy_PlayerFlamethrowerSound.wav"); // 1
      audioManager->AddChunk("./audio/Reload.wav");                        // 2
      audioManager->AddChunk("./audio/OutOfAmmo.wav");                     // 3
      audioManager->AddChunk("./audio/smash.wav");                         // 4
      audioManager->AddChunk("./audio/player_hurt.wav");                   // 5
      audioManager->AddChunk("./audio/Minor_Explosion.wav");               // 6
      audioManager->AddChunk("./audio/glass_shatter.wav");                 // 7
}

void LevelOne::SetupLevel()
{
      SDL_ShowCursor(0);

      // player
      player = new Player(glm::vec2(300, windowHeight * 2 / 3), glm::vec2(600.0, 600.0), 250, this, windowWidth, windowHeight);

      // facehugger tanks
      InstantiateGameObject(new FacehuggerTank(glm::vec2(1000.0, 420), 256, player, this));

      InstantiateGameObject(player); // create render layers

      // managers
      spawnManager = new LevelOneSpawnManager(player, this);
      spawnManager->CreateSpawnObject("Alien", 20.0);
      spawnManager->CreateSpawnObject("AlienEgg", 25.0);

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
      InstantiateGameObject(new Mine(glm::vec2(2000, 700), 64, this));
      InstantiateGameObject(new Mine(glm::vec2(4000, 750), 64, this));
      InstantiateGameObject(new Mine(glm::vec2(6000, 800), 64, this));
      InstantiateGameObject(new Mine(glm::vec2(8000, 750), 64, this));

      Level::SetupLevel();
}
