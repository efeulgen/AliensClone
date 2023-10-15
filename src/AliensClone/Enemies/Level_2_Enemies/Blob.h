
#ifndef BLOB_H
#define BLOB_H

#include <cstdlib>
#include "../../../Engine/GameObject.h"
#include "../../../Engine/Level.h"
#include "../../Player.h"

enum BlobAnimState
{
      BAS_Blobbing,
      BAS_Dropping,
      BAS_Dissolving
};

class Blob : public GameObject
{
private:
      Player *refToPlayer = nullptr;
      Level *refToCurrentLevel = nullptr;

      // animations
      BlobAnimState animState;

      double blobbingAnimIndex = 0.0;
      const char *blobbingSpriteSheet[4] = {"./assets/sprites/Enemies/Blob/Blob_blobbing_1.png", "./assets/sprites/Enemies/Blob/Blob_blobbing_2.png", "./assets/sprites/Enemies/Blob/Blob_blobbing_3.png", "./assets/sprites/Enemies/Blob/Blob_blobbing_4.png"};

      double dissolvingAnimIndex = 0.0;
      const char *dissolvingSpriteSheet[4] = {"./assets/sprites/Enemies/Blob/Blob_dissolving_1.png", "./assets/sprites/Enemies/Blob/Blob_dissolving_2.png", "./assets/sprites/Enemies/Blob/Blob_dissolving_3.png", "./assets/sprites/Enemies/Blob/Blob_dissolving_4.png"};

public:
      Blob(glm::vec2 pos, glm::vec2 vel, int rSize, Player *p, Level *l);
      ~Blob();

      void InitGameObject() override;
      void UpdateGameObject(double deltaTime) override;
      void RenderGameObject(SDL_Renderer *renderer) override;
      void CollisionCallback(GameObject *otherObj, SDL_Rect *hitRect) override;
};

#endif
