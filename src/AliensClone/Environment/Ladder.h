
#ifndef LADDER_H
#define LADDER_H

#include "../../Engine/GameObject.h"

class Ladder : public GameObject
{
public:
      Ladder(glm::vec2 pos, int rSizeX, int rSizeY);
      ~Ladder();
};

#endif
