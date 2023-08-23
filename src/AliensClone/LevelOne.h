
#ifndef LEVELONE_H
#define LEVELONE_H

#include "../Engine/Level.h"

class LevelOne : public Level
{
public:
      LevelOne();
      ~LevelOne();

      void SetupLevel() override;
      void UpdateLevel(double deltaTime) override;
      void RenderLevel(SDL_Renderer *renderer) override;
};

#endif
