
#include "LevelTwo.h"

LevelTwo::LevelTwo(int index, int w, int h, int len, GameManager *gManager, bool isFinal) : Level(index, w, h, len, gManager, isFinal)
{
      Logger::Logg("LevelTwo Constructor");

      levelBackgroundPath = "./assets/sprites/Background_2.png";
}

LevelTwo::~LevelTwo()
{
      Logger::Logg("LevelTwo Destructor");
}

void LevelTwo::SetupLevelSounds()
{
      audioManager->AddChunk("./audio/dummy_PlayerLaserBlasterSound.wav"); // 0
      audioManager->AddChunk("./audio/dummy_PlayerFlamethrowerSound.wav"); // 1
      audioManager->AddChunk("./audio/Reload.wav");                        // 2
      audioManager->AddChunk("./audio/OutOfAmmo.wav");                     // 3
      audioManager->AddChunk("./audio/smash.wav");                         // 4
      audioManager->AddChunk("./audio/player_hurt.wav");                   // 5
      audioManager->AddChunk("./audio/Minor_Explosion.wav");               // 6
}

void LevelTwo::SetupLevel()
{
      SDL_ShowCursor(0);

      // player
      player = new Player(glm::vec2(300, windowHeight * 2 / 3), glm::vec2(600.0, 600.0), 250, this, windowWidth, windowHeight);
      InstantiateGameObject(player);

      // managers
      spawnManager = new LevelTwoSpawnManager();
      uiManager = new LevelTwoUIManager(windowWidth, windowHeight, player, refToGameManager);

      // pickups

      Level::SetupLevel();
}
