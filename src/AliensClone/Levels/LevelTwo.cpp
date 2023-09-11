
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

void LevelTwo::SetupLevel()
{
      SDL_ShowCursor(0);

      // player
      player = new Player(glm::vec2(300, windowHeight * 2 / 3), glm::vec2(600.0, 600.0), 250, this, windowWidth, windowHeight);
      gameObjects.push_back(player);

      // spawn manager

      // pickups

      Level::SetupLevel();

      // uiManager->SetRefToPlayer(player);
}
