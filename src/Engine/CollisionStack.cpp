
#include "CollisionStack.h"

CollisionStack::CollisionStack()
{
      // Logger::Log("CollisionStack Constructor");
}

CollisionStack::~CollisionStack()
{
      // Logger::Log("CollisionStack Destructor");
}

void CollisionStack::AddCollisionObject(int id)
{
      CollisionStackNode *newCollisionObj = new CollisionStackNode;
      newCollisionObj->id = id;

      newCollisionObj->next = nullptr;

      if (first == nullptr)
      {
            first = last = newCollisionObj;
      }
      else
      {
            last->next = newCollisionObj;
            last = newCollisionObj;
      }
}

void CollisionStack::DeleteCollisionObject(int id)
{
      CollisionStackNode *p = first;
      CollisionStackNode *q = nullptr;
      while (p->id != id)
      {
            q = p;
            p = p->next;
      }
      if (q)
      {
            q->next = p->next;
      }
      else
      {
            first = last = nullptr;
      }
      delete p;
}

bool CollisionStack::FindCollisionObjectWithID(int id)
{
      CollisionStackNode *p = first;
      while (p)
      {
            if (p->id == id)
            {
                  return true;
            }
            p = p->next;
      }
      return false;
}
