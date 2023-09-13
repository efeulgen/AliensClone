
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
}

void LevelOne::SetupLevel()
{
      SDL_ShowCursor(0);

      // player
      player = new Player(glm::vec2(300, windowHeight * 2 / 3), glm::vec2(600.0, 600.0), 250, this, windowWidth, windowHeight);
      gameObjects.push_back(player);

      // manager
      spawnManager = new LevelOneSpawnManager(player, this);
      spawnManager->SpawnGameObject("Alien", 20.0);
      spawnManager->SpawnGameObject("AlienEgg", 25.0);

      uiManager = new LevelOneUIManager(windowWidth, windowHeight, player, refToGameManager);

      // pickups
      gameObjects.push_back(new Pickup(glm::vec2(800, 600), 128, PickupType::PT_HealthPickup));
      gameObjects.push_back(new Pickup(glm::vec2(1200, 600), 128, PickupType::PT_LaserBlasterAmmoPickup));
      gameObjects.push_back(new Pickup(glm::vec2(1700, 600), 128, PickupType::PT_HealthPickup));
      gameObjects.push_back(new Pickup(glm::vec2(2300, 600), 128, PickupType::PT_FlamethrowerAmmoPickup));
      gameObjects.push_back(new Pickup(glm::vec2(2800, 600), 128, PickupType::PT_TrippleShotAmmoPickup));

      Level::SetupLevel();
}
