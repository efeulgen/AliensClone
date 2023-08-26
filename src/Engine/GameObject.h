
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
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
      Transform transform;
      glm::vec2 velocity = glm::vec2(0.0, 0.0);
      int rectSize = 0;
      const char *imgFilePath = nullptr;

      bool isFlipped = false;
      bool canBeDestroyed = false;

private:
      SDL_Rect rect = {0, 0, 0, 0};

public:
      GameObject() {}
      GameObject(glm::vec2 pos, glm::vec2 vel, int rSize)
      {
            transform.position = pos;
            velocity = vel;
            rectSize = rSize;
      }

      virtual ~GameObject() {}
      virtual void InitGameObject() = 0;
      virtual void CollisionCallback() = 0;
      virtual void UpdateGameObject(double deltaTime) = 0;

      virtual void RenderGameObject(SDL_Renderer *renderer)
      {
            SDL_Surface *surf = IMG_Load(imgFilePath);
            SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
            rect = {static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    static_cast<int>(rectSize * transform.scale.x),
                    static_cast<int>(rectSize * transform.scale.y)};
            if (isFlipped)
            {
                  SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
                  SDL_RenderCopyEx(renderer, tex, NULL, &rect, 0.0, NULL, flip);
            }
            else
            {
                  SDL_RenderCopy(renderer, tex, NULL, &rect);
            }
            SDL_DestroyTexture(tex);
      }

      void CheckCollision(SDL_Rect other)
      {
            if (SDL_HasIntersection(&rect, &other))
            {
                  CollisionCallback();
            }
      }

      void DestroyGameObject() { delete this; }

      // getters & setters
      SDL_Rect GetRect() const { return rect; }
      Transform GetTransform() const { return transform; }
      bool GetCanBeDestroyed() const { return canBeDestroyed; }
};

#endif
