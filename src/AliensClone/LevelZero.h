
#ifndef LEVELZERO_H
#define LEVELZERO_H

#include "../Engine/Level.h"

class LevelZero : public Level
{
public:
      LevelZero();
      ~LevelZero();

      void SetupLevel() override;
      void UpdateLevel(double deltaTime) override;
      void RenderLevel(SDL_Renderer *renderer) override;
};

#endif
