
#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "../../Engine/Level.h"

class LevelThree : public Level
{
public:
      LevelThree(int index, int w, int h, int len, GameManager *gManager, bool isFinal = false);
      ~LevelThree();

      void SetupLevel() override;
};

#endif
