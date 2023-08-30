
#include "LevelOne.h"

LevelOne::LevelOne(int index, int w, int h) : Level(index, w, h)
{
      Logger::Logg("LevelOne Constructor");

      levelBackgroundPath = "./assets/sprites/Background_1.png";
}

LevelOne::~LevelOne()
{
      Logger::Logg("LevelOne Destructor");
}

void LevelOne::SetupLevel()
{
      // managers
      audioManager = new AudioManager();
      levelManager = new LevelManager();
      spawnManager = new SpawnManager;
      uiManager = new UIManager(windowWidth, windowHeight);

      // player
      player = new Player(glm::vec2(300, windowHeight * 2 / 3), glm::vec2(600.0, 600.0), 250, this, windowWidth, windowHeight);
      gameObjects.push_back(player);

      // pickups
      gameObjects.push_back(new Pickup(glm::vec2(800, 600), 128, PickupType::PT_HealthPickup));
      gameObjects.push_back(new Pickup(glm::vec2(1200, 600), 128, PickupType::PT_LaserBlasterAmmoPickup));

      Level::SetupLevel();
}
