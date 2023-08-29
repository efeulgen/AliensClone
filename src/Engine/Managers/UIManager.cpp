
#include "UIManager.h"

UIManager::UIManager(int w, int h) : windowWidth{w}, windowHeight{h}
{
      Logger::Logg("UIManager Constructor");
}

UIManager::~UIManager()
{
      Logger::Logg("UIManager Destructor");

      TTF_CloseFont(font);
      font = nullptr;
      free(font);
}

void UIManager::RenderImage(SDL_Renderer *renderer, const char *imgFilePath, glm::vec2 pos)
{

      SDL_Surface *surf = IMG_Load(imgFilePath);
      SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
      double x_pos = pos.x >= 0 ? pos.x : windowWidth / 2 - surf->w / 2;
      double y_pos = pos.y >= 0 ? pos.y : windowHeight / 2 - surf->h / 2;
      SDL_Rect rect = {static_cast<int>(x_pos), static_cast<int>(y_pos), surf->w, surf->h};
      SDL_FreeSurface(surf);
      SDL_RenderCopy(renderer, tex, NULL, &rect);
      SDL_DestroyTexture(tex);
}

void UIManager::RenderText(SDL_Renderer *renderer, const std::string &text, Uint8 r, Uint8 g, Uint8 b, glm::vec2 textPos)
{
      SDL_Color color = {r, g, b};
      SDL_Surface *surf = TTF_RenderText_Solid(font, text.c_str(), color);
      SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
      double x_pos = textPos.x >= 0 ? textPos.x : windowWidth / 2 - surf->w / 2;
      double y_pos = textPos.y >= 0 ? textPos.y : windowHeight / 2 - surf->h / 2;
      SDL_Rect rect = {static_cast<int>(x_pos), static_cast<int>(y_pos), surf->w, surf->h};
      SDL_FreeSurface(surf);
      SDL_RenderCopy(renderer, tex, NULL, &rect);
      SDL_DestroyTexture(tex);
}

void UIManager::RenderUI()
{
}
