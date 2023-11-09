
#include "CollisionStack.h"

CollisionStack::CollisionStack()
{
      Logger::Log("CollisionStack Constructor");
}

CollisionStack::~CollisionStack()
{
      Logger::Log("CollisionStack Destructor");
}

void CollisionStack::AddCollisionObject(std::string colliderTag)
{
      CollisionStackNode *newCollisionObj = new CollisionStackNode;
      newCollisionObj->tag = colliderTag;
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

void CollisionStack::DeleteCollisionObject(std::string colliderTag)
{
      CollisionStackNode *p = first;
      CollisionStackNode *q = nullptr;
      while (p->tag != colliderTag)
      {
            q = p;
            p = p->next;
      }
      q->next = p->next;
      delete p;
}

bool CollisionStack::FindCollisionObjectWithTag(std::string tag)
{
      CollisionStackNode *p = first;
      while (p)
      {
            if (p->tag == tag)
            {
                  return true;
            }
            p = p->next;
      }
      return false;
}
