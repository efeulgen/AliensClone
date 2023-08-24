
#ifndef LEVELONE_H
#define LEVELONE_H

#include "../Engine/Level.h"

class LevelOne : public Level
{
public:
      LevelOne(int index, int w, int h);
      ~LevelOne();

      void SetupLevel() override;
};

#endif
