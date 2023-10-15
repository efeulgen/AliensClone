
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "Logger/Logger.h"
#include "Managers/AudioManager.h"

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
      std::string gameObjectTag = "Untagged";

      bool isFlipped = false;
      bool canBeDestroyed = false;

      SDL_Rect colliderRect = {0, 0, 0, 0};

private:
      int gameObjectID;

      SDL_Rect rect = {0, 0, 0, 0};
      SDL_Rect *collisionRect = new SDL_Rect;

public:
      GameObject() {}
      GameObject(glm::vec2 pos, int rSize)
      {
            transform.position = pos;
            rectSize = rSize;
      }
      GameObject(glm::vec2 pos, glm::vec2 vel, int rSize)
      {
            transform.position = pos;
            velocity = vel;
            rectSize = rSize;
      }

      virtual ~GameObject()
      {
            delete collisionRect;
      }

      virtual void InitGameObject() {}                                           // = 0;
      virtual void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) {} //  = 0;
      virtual void UpdateGameObject(double deltaTime) {}                         // = 0;

      virtual void RenderGameObject(SDL_Renderer *renderer)
      {
            SDL_Surface *surf = IMG_Load(imgFilePath);
            SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
            CalculateRect();
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

      virtual void CalculateRect()
      {
            rect = {static_cast<int>(transform.position.x),
                    static_cast<int>(transform.position.y),
                    static_cast<int>(rectSize * transform.scale.x),
                    static_cast<int>(rectSize * transform.scale.y)};
            CalculateColliderRect();
      }

      virtual void CalculateColliderRect()
      {
            colliderRect = {static_cast<int>(transform.position.x),
                            static_cast<int>(transform.position.y),
                            static_cast<int>(rectSize * transform.scale.x),
                            static_cast<int>(rectSize * transform.scale.y)};
      }

      virtual void RenderAnimation(SDL_Renderer *renderer, const char *spriteSheet[], int spriteSheetSize, int spriteSize, double *sprtieSheetIndex, glm::vec2 pos, bool playOnce, bool flip = false)
      {
            if (static_cast<int>(*sprtieSheetIndex) >= spriteSheetSize - 1 && !playOnce)
            {
                  *sprtieSheetIndex = 0.0;
            }

            SDL_Surface *surf = IMG_Load(spriteSheet[static_cast<int>(*sprtieSheetIndex)]);
            SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
            SDL_Rect rect = {static_cast<int>(pos.x), static_cast<int>(pos.y), spriteSize, spriteSize};
            if (flip)
            {
                  SDL_RendererFlip flipped = SDL_FLIP_HORIZONTAL;
                  SDL_RenderCopyEx(renderer, tex, NULL, &rect, 0.0, NULL, flipped);
            }
            else
            {
                  SDL_RenderCopy(renderer, tex, NULL, &rect);
            }
            SDL_DestroyTexture(tex);
      }

      void CheckCollision(SDL_Rect other, GameObject *otherObj)
      {
            if (SDL_HasIntersection(&colliderRect, &other))
            {
                  SDL_IntersectRect(&colliderRect, &other, collisionRect);
                  CollisionCallback(otherObj, collisionRect);
            }
      }

      void ShiftGameObject(double shiftValue, double deltaTime)
      {
            transform.position.x -= shiftValue * deltaTime;
      }

      void DestroyGameObject() { delete this; }

      // *************** getters & setters *********************************************
      SDL_Rect GetRect() const { return rect; }
      SDL_Rect GetColliderRect() const { return colliderRect; }

      glm::vec2 GetRectMidTop() const { return glm::vec2(rect.x + (rect.w / 2), rect.y); }
      glm::vec2 GetRectMidBottom() const { return glm::vec2(rect.x + (rect.w / 2), rect.y + rect.h); }
      glm::vec2 GetRectMidLeft() const { return glm::vec2(rect.x, rect.y + (rect.y / 2)); }
      glm::vec2 GetRectMidRight() const { return glm::vec2(rect.x + rect.w, rect.y + (rect.y / 2)); }

      Transform GetTransform() const { return transform; }
      glm::vec2 GetPosition() const { return transform.position; }

      bool GetCanBeDestroyed() const { return canBeDestroyed; }
      void SetCanBeDestroyed(bool value) { canBeDestroyed = value; }

      std::string GetGameObjectTag() const { return gameObjectTag; }
      int GetGameObjectID() const { return gameObjectID; }
};

#endif
