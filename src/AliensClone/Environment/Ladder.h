
#ifndef LADDER_H
#define LADDER_H

#include "../../Engine/GameObject.h"

class Ladder : public GameObject
{
public:
      Ladder(glm::vec2 pos, int rSize);
      ~Ladder();
};

#endif
