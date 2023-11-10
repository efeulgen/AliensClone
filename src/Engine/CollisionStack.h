
#ifndef COLLISIONSTACK_H
#define COLLISIONSTACK_H

#include <iostream>
#include "Logger/Logger.h"

struct CollisionStackNode
{
      std::string tag = "";
      CollisionStackNode *next = nullptr;
};

class CollisionStack
{
private:
      CollisionStackNode *first = nullptr;
      CollisionStackNode *last = nullptr;

public:
      CollisionStack();
      ~CollisionStack();

      void AddCollisionObject(std::string colliderTag);
      void DeleteCollisionObject(std::string colliderTag);
      bool FindCollisionObjectWithTag(std::string colliderTag);
};

#endif
