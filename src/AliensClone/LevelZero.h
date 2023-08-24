
#ifndef LEVELZERO_H
#define LEVELZERO_H

#include "../Engine/Level.h"
#include "Player.h"

class LevelZero : public Level
{
public:
      LevelZero();
      ~LevelZero();

      void SetupLevel() override;
};

#endif
