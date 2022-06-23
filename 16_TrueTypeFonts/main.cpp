#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <cstddef>
#include <stdio.h>
#include <string>

bool init();
bool loadMedia();
void close();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

TTF_Font *gFont = NULL;
LTexture gTextTexture;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
  // init SDL
  if (!init()) {
    printf("Failed to initialize");
  } else {
    if (!loadMedia()) {
      printf("Failed to load meadia");
    } else {
      bool quit = false;
      SDL_Event e;
      double degrees = 0;
      SDL_RendererFlip flipType = SDL_FLIP_NONE;

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2,
                            (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2,
                            gRenderer);

        SDL_RenderPresent(gRenderer);
      }
    }
  }
  close();
  return 0;
}

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    gWindow = SDL_CreateWindow("SDL Tuturial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("SDL could not creat a window SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gRenderer = SDL_CreateRenderer(
          gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL) {
        printf("Couldn't create  renderer! Err: %s \n", SDL_GetError());
        success = false;
      } else {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("could not initializy SDL_image! Err: %s\n", IMG_GetError());
          success = false;
        }
        if (TTF_Init() == -1) {
          printf("SDL_ttf could not be inited! Error: %s\n", TTF_GetError());
          success = false;
        }
      }
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;

  gFont = TTF_OpenFont("assets/fonts/lazy.ttf", 28);
  if (gFont == NULL) {
    printf("failed to load font! Error: %s\n", TTF_GetError());
  } else {
    SDL_Colour textColour = {0, 0, 0};
    if (!gTextTexture.loadFromRenderedText(
            "The quick brown fox jumps over the lazy dog", textColour, gFont,
            gRenderer)) {
      printf("failed to render text texture\n");
      success = false;
    }
  }

  return success;
}

void close() {
  gTextTexture.freeTexture();

  TTF_CloseFont(gFont);
  gFont = NULL;

  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);

  gRenderer = NULL;
  gWindow = NULL;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
