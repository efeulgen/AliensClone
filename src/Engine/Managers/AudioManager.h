
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <iostream>
#include <vector>
#include <SDL2/SDL_mixer.h>
#include "../Logger/Logger.h"

struct sfx
{
      Mix_Chunk *chunk = nullptr;
      int channel;
      bool isPlaying;
};

class AudioManager
{
private:
      std::vector<sfx> soundEffects;

public:
      AudioManager();
      ~AudioManager();

      void AddChunk(const char *filePath);
      void PlaySFX(int index);
      void StopSFX(int index);
      void ClearSoundEffects();
};

#endif
