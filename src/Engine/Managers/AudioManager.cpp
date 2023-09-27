
#include "AudioManager.h"

AudioManager::AudioManager()
{
      Logger::Logg("AudioManager Constructor");
}

AudioManager::~AudioManager()
{
      Logger::Logg("AudioManager Destructor");

      ClearSoundEffects();
}

void AudioManager::AddChunk(const char *filePath)
{
      Mix_Chunk *newChunk = Mix_LoadWAV(filePath);
      sfx newSFX = {newChunk, 0, false};
      soundEffects.push_back(newSFX);
}

void AudioManager::PlaySFX(int index)
{
      soundEffects[index].channel = Mix_PlayChannel(-1, soundEffects[index].chunk, 0);
      soundEffects[index].isPlaying = true;
}

void AudioManager::StopSFX(int index)
{
      if (soundEffects[index].isPlaying)
      {
            Mix_HaltChannel(soundEffects[index].channel);
            soundEffects[index].isPlaying = false;
      }
}

void AudioManager::ClearSoundEffects()
{
      for (auto effect : soundEffects)
      {
            Mix_FreeChunk(effect.chunk);
      }
      soundEffects.clear();
}
