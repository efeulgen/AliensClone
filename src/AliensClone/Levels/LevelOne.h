
#ifndef LEVELZERO_H
#define LEVELZERO_H

#include "../../Engine/Level.h"
#include "../Player.h"
#include "../Pickups/Pickup.h"

class LevelOne : public Level
{
public:
      LevelOne(int index, int w, int h);
      ~LevelOne();

      void SetupLevel() override;
};

#endif
