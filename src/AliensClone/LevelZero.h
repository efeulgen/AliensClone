
#ifndef LEVELZERO_H
#define LEVELZERO_H

#include "../Engine/Level.h"
#include "Player.h"
#include "Pickups/Pickup.h"

class LevelZero : public Level
{
public:
      LevelZero(int index, int w, int h);
      ~LevelZero();

      void SetupLevel() override;
};

#endif
