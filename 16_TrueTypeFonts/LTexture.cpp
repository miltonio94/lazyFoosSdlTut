#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>

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

bool LTexture::loadFromRenderedText(std::string textureText,
                                    SDL_Color textColour, TTF_Font *font,
                                    SDL_Renderer *renderer) {
  freeTexture();

  SDL_Surface *textSurface =
      TTF_RenderText_Solid(font, textureText.c_str(), textColour);

  if (textSurface == NULL) {
    printf("Unable to render text surface! SDL Error: %s\n", SDL_GetError());
  }
  mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  if (mTexture == NULL) {
    printf("unable to create texture from font! error: %s", SDL_GetError());
  } else {
    mWidth = textSurface->w;
    mHeight = textSurface->h;
  }
  SDL_FreeSurface(textSurface);

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

void LTexture::render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip) {
  SDL_Rect renderQuad = {x, y, clip->w, clip->h};

  SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

void LTexture::render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip,
                      double angle, SDL_Point *center, SDL_RendererFlip flip) {
  SDL_Rect renderQuad = {x, y, clip->w, clip->h};

  SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::render(int x, int y, SDL_Renderer *renderer, double angle,
                      SDL_RendererFlip flip) {
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  SDL_RenderCopyEx(renderer, mTexture, NULL, &renderQuad, angle, NULL, flip);
}

void LTexture::render(int x, int y, SDL_Renderer *renderer) {
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blender) {
  SDL_SetTextureBlendMode(mTexture, blender);
}

void LTexture::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(mTexture, alpha);
}
