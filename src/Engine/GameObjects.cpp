
#include "GameObjects.h"

GameObjects::GameObjects()
{
      Logger::Logg("GameObjects Constructor");
}

GameObjects::~GameObjects()
{
      Logger::Logg("GameObjects Destructor");
}

void GameObjects::InstantiateGameObject(GameObject *newObj)
{
      newObj->InitGameObject();

      GameObject **temp = new GameObject *[length + 1];
      int i;
      for (i = 0; i < length; i++)
      {
            temp[i] = gameObjects[i];
      }
      temp[i + 1] = newObj;

      gameObjects = temp;
      delete[] temp;
      temp = nullptr;
      length++;
}

GameObject *GameObjects::FindGameObject(GameObject *obj)
{
      return nullptr;
}

GameObject *GameObjects::FindGameObjectWithTag(std::string tag)
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

void GameObjects::DestroyGameObject(GameObject *obj)
{
      if (!obj)
            return;

      delete obj;
      obj = nullptr;

      GameObject **temp = new GameObject *[length - 1];

      int i, j;
      for (i = 0, j = 0; i < length; i++, j++)
      {
            if (gameObjects[i] == nullptr)
            {
                  i++;
            }
            else
            {
                  temp[j] = gameObjects[i];
            }
      }

      gameObjects = temp;
      delete[] temp;
      temp = nullptr;
      length--;
}

void GameObjects::DestroyGameObjectWithTag(std::string tag)
{
      DestroyGameObject(FindGameObjectWithTag(tag));
}

void GameObjects::ClearGameObjects()
{
      for (int i = 0; i < length; i++)
      {
            delete gameObjects[i];
            gameObjects[i] = nullptr;
      }
      delete[] gameObjects;
      gameObjects = nullptr;
}
