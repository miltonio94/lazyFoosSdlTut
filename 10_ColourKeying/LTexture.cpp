#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include <SDL2/SDL_pixels.h>
// #include <SDL2/SDL_rect.h>
// #include <SDL2/SDL_render.h>
// #include <SDL2/SDL_stdinc.h>
// #include <SDL2/SDL_surface.h>
#include <cstddef>

LTexture::LTexture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture() { freeTexture(); }

bool LTexture::loadFromFile(std::string path, SDL_Renderer *renderer) {
  freeTexture();

  SDL_Texture *newTexture = NULL;
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());

  if (loadedSurface == NULL) {
    printf("Failed to load image %s! Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    SDL_SetColorKey(loadedSurface, SDL_TRUE,
                    SDL_MapRGB(loadedSurface->format, 0, 0xff, 0xff));
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if (newTexture == NULL) {
      printf("Unable to transform surface %s into a texture! SDL Error: %s \n",
             path.c_str(), SDL_GetError());
    } else {
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }
    SDL_FreeSurface(loadedSurface);
  }
  mTexture = newTexture;
  return mTexture != NULL;
}

void LTexture::freeTexture() {
  if (mTexture != NULL) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::render(int x, int y, SDL_Renderer *renderer) {
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};
  SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }
