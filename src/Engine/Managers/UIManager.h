
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include "../Logger/Logger.h"

class UIManager
{
private:
      TTF_Font *font = TTF_OpenFont("./assets/font/LazenbyCompSmooth.ttf", 32);
      int windowWidth;
      int windowHeight;

public:
      UIManager(int w, int h);
      ~UIManager();

      void RenderImage(SDL_Renderer *renderer, const char *imgFilePath, glm::vec2 pos = glm::vec2(-1, -1));
      void RenderText(SDL_Renderer *renderer, const std::string &text, Uint8 r, Uint8 g, Uint8 b, glm::vec2 textPos = glm::vec2(-1, -1));
      void RenderUI();
};

#endif
