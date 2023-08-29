
#ifndef LEVELONE_H
#define LEVELONE_H

#include "../../Engine/Level.h"

class LevelTwo : public Level
{
public:
      LevelTwo(int index, int w, int h);
      ~LevelTwo();

      void SetupLevel() override;
};

#endif
