
#ifndef POSSESSED_H
#define POSSESSED_H

#include "../../../Engine/GameObject.h"

class Possessed : public GameObject
{
public:
      Possessed(glm::vec2 pos, int rSize);
      ~Possessed();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
