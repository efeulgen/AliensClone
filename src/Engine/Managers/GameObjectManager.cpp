
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
      Logger::Log("GameObjectManager Constructor");
}

GameObjectManager::~GameObjectManager()
{
      Logger::Log("GameObjectManager Destructor");
}

// **********************************************************************************************************************************************************************************************
// **********************************************************************************************************************************************************************************************
// **********************************************************************************************************************************************************************************************

void GameObjectManager::InstantiateGameObject(GameObject *newObj)
{
      newObj->InitGameObject();

      GameObject **temp = new GameObject *[length + 1];
      int i;
      for (i = 0; i < length; i++)
      {
            temp[i] = gameObjects[i];
      }
      temp[length] = newObj;

      delete[] gameObjects;
      gameObjects = temp;
      temp = nullptr;

      length++;
}

GameObject *GameObjectManager::FindGameObject(GameObject *obj)
{
      int low, mid, high;
      low = 0;
      high = length - 1;

      while (low <= high)
      {
            mid = (low + high) / 2;
            if (obj->GetGameObjectID() == gameObjects[mid]->GetGameObjectID())
            {
                  return gameObjects[mid];
            }
            else if (obj->GetGameObjectID() < gameObjects[mid]->GetGameObjectID())
            {
                  high = mid - 1;
            }
            else
            {
                  low = mid + 1;
            }
      }

      return nullptr;
}

GameObject *GameObjectManager::FindGameObjectWithTag(std::string tag)
{
      for (int i = 0; i < length; i++)
      {
            if (gameObjects[i]->GetGameObjectTag() == tag)
            {
                  return gameObjects[i];
            }
      }
      return nullptr;
}

void GameObjectManager::DestroyGameObject(GameObject *obj)
{
      if (!obj)
            return;

      GameObject **temp = new GameObject *[length - 1];

      int i, j;
      for (i = 0, j = 0; i < length; i++, j++)
      {
            if (gameObjects[i] == obj)
            {
                  delete gameObjects[i];
                  gameObjects[i] = nullptr;
                  j--;
            }
            else
            {
                  temp[j] = gameObjects[i];
            }
      }
      delete[] gameObjects;
      gameObjects = temp;
      temp = nullptr;

      length--;
}

void GameObjectManager::DestroyGameObjectWithTag(std::string tag)
{
      DestroyGameObject(FindGameObjectWithTag(tag));
}

void GameObjectManager::ClearGameObjects()
{
      for (int i = 0; i < length; i++)
      {
            delete gameObjects[i];
            gameObjects[i] = nullptr;
      }
      delete[] gameObjects;
      gameObjects = nullptr;
      length = 0;
}

void GameObjectManager::SortRenderPriority()
{
      for (int i = 0; i < length - 1; i++)
      {
            if (gameObjects[i]->GetRenderPriority() > gameObjects[i + 1]->GetRenderPriority())
            {
                  GameObject *temp = gameObjects[i];
                  gameObjects[i] = gameObjects[i + 1];
                  gameObjects[i + 1] = temp;
                  temp = nullptr;
            }
      }
}

bool GameObjectManager::isEmpty() const
{
      return length == 0;
}
