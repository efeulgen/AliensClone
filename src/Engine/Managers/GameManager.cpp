
#include "GameManager.h"

GameManager::GameManager()
{
    Logger::Logg("GameManager Constructor");

    isRunning = false;
    isGameStarted = false;
    isPlayerDead = false;
    isGameOver = false;
}

GameManager::~GameManager()
{
    Logger::Logg("GameManager Destructor");
}
