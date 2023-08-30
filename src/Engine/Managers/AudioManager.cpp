
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
      sfx newSFX = {newChunk, 0};
      soundEffects.push_back(newSFX);
}

void AudioManager::PlaySFX(int index)
{
      soundEffects[index].channel = Mix_PlayChannel(-1, soundEffects[index].chunk, 0);
}

void AudioManager::StopSFX(int index)
{
      Mix_HaltChannel(soundEffects[index].channel);
}

void AudioManager::ClearSoundEffects()
{
      for (auto effect : soundEffects)
      {
            Mix_FreeChunk(effect.chunk);
      }
      soundEffects.clear();
}
