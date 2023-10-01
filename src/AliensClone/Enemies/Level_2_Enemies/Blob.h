
#ifndef BLOB_H
#define BLOB_H

#include "../../../Engine/GameObject.h"

class Blob : public GameObject
{
public:
      Blob(glm::vec2 pos, int rSize);
      ~Blob();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
