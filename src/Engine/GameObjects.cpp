
#include "GameObjects.h"

GameObjects::GameObjects(int initSize) : size{initSize}
{
      Logger::Logg("GameObjects Constructor");

      // gameObjects = new GameObject[size];
}

GameObjects::~GameObjects()
{
      Logger::Logg("GameObjects Destructor");
}

void GameObjects::InitGameObjects()
{
}

void GameObjects::UpdateGameObjects(double deltaTime)
{
}

void GameObjects::RenderGameObjects(SDL_Renderer *renderer)
{
}

void GameObjects::AppendGameObject(GameObject obj)
{
}

GameObject GameObjects::FindGameObjectWithTag(std::string tag)
{
}

void GameObjects::RemoveGameObjectWithTag(std::string tag)
{
}

void GameObjects::ClearGameObjects()
{
}
