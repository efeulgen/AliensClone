
#ifndef LEVELONE_H
#define LEVELONE_H

#include "../Engine/Level.h"

class LevelOne : public Level
{
public:
      LevelOne();
      ~LevelOne();

      void SetupLevel() override;
};

#endif
