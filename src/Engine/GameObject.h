
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "Logger/Logger.h"

struct Transform
{
      glm::vec2 position = glm::vec2(0.0, 0.0);
      glm::vec2 scale = glm::vec2(1.0, 1.0);
      double rotation = 0.0;
};

class GameObject
{
protected:
      SDL_Rect rect = {0, 0, 0, 0};
      Transform transform;
      glm::vec2 velocity = glm::vec2(0.0, 0.0);
      const char *imgFilePath = nullptr;

public:
      GameObject()
      {
      }
      virtual ~GameObject() {}

      virtual void InitGameObject() = 0;
      virtual void UpdateGameObject(double deltaTime) = 0;
      virtual void RenderGameObject(SDL_Renderer *renderer)
      {
            SDL_Surface *surf = IMG_Load(imgFilePath);
            SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
            rect = {static_cast<int>(transform.position.x), static_cast<int>(transform.position.y), 64, 64}; // change 64 later
            SDL_RenderCopy(renderer, tex, NULL, &rect);
            SDL_DestroyTexture(tex);
      }

      void DestroyGameObject()
      {
            delete this;
      }

      // getters & setters
      SDL_Rect GetRect() const { return rect; }
      Transform GetTransform() const { return transform; }
};

#endif
