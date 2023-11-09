
#include "GameManager.h"

GameManager::GameManager()
{
    Logger::Log("GameManager Constructor");

    isRunning = false;
    isGameStarted = false;
    isPlayerDead = false;
    isGameOver = false;
}

GameManager::~GameManager()
{
    Logger::Log("GameManager Destructor");
}
