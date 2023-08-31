
#ifndef LEVELZERO_H
#define LEVELZERO_H

#include "../../Engine/Level.h"
#include "../Player.h"
#include "../Enemies/Alien.h" // for testing
#include "../Pickups/Pickup.h"

class LevelOne : public Level
{
public:
      LevelOne(int index, int w, int h, int len, GameManager *gManager, bool isFinal = false);
      ~LevelOne();

      void SetupLevel() override;
};

#endif
