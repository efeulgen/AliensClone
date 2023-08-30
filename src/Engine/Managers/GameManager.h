
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../Logger/Logger.h"

class GameManager
{
private:
      bool isRunning; // static?
      bool isGameStarted;
      bool isPlayerDead;
      bool isGameOver;

public:
      GameManager();
      ~GameManager();

      // getters & setters
      bool GetIsRunning() const { return isRunning; }
      void SetIsRunning(bool value) { isRunning = value; }

      bool GetIsGameStarted() const { return isGameStarted; }
      void SetIsGameStarted(bool value) { isGameStarted = value; }

      bool GetIsPlayerDead() const { return isPlayerDead; }
      void SetIsPlayerDead(bool value) { isPlayerDead = value; }

      bool GetIsGameOver() const { return isGameOver; }
      void SetIsGameOver(bool value) { isGameOver = value; }
};

#endif
