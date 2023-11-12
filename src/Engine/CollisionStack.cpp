
#include "CollisionStack.h"

CollisionStack::CollisionStack()
{
      // Logger::Log("CollisionStack Constructor");
}

CollisionStack::~CollisionStack()
{
      // Logger::Log("CollisionStack Destructor");
}

void CollisionStack::AddCollisionObject(int objId)
{
      CollisionStackNode *newCollisionObj = new CollisionStackNode;
      newCollisionObj->id = objId;

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

void CollisionStack::DeleteCollisionObject(int objId)
{
      CollisionStackNode *p = first;
      CollisionStackNode *q = nullptr;
      while (p->id != objId)
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
      p = nullptr;
}

bool CollisionStack::FindCollisionObjectWithID(int objId)
{
      CollisionStackNode *p = first;
      while (p)
      {
            if (p->id == objId)
            {
                  p = nullptr;
                  return true;
            }
            p = p->next;
      }
      p = nullptr;
      return false;
}

void CollisionStack::ClearCollisionStack()
{
      CollisionStackNode *p = first;
      CollisionStackNode *q = nullptr;
      while (p)
      {
            q = p;
            p = p->next;
            delete q;
            q = nullptr;
      }
}

void CollisionStack::DisplayCollisionStack(std::string tag)
{
      if (!first)
      {
            std::cout << "Collision stack of " << tag << " is empty." << std::endl;
      }
      CollisionStackNode *p = first;
      while (p)
      {
            std::cout << "Collision stack of " << tag << " : " << p->id << std::endl;
            p = p->next;
      }
}
