
#ifndef COLLISIONSTACK_H
#define COLLISIONSTACK_H

#include <iostream>
#include "Logger/Logger.h"

struct CollisionStackNode
{
      int id = -1;
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

      void AddCollisionObject(int objId);
      void DeleteCollisionObject(int objId);
      bool FindCollisionObjectWithID(int objId);
      void ClearCollisionStack();
      void DisplayCollisionStack(std::string tag);
};

#endif
