#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <cstdio>
#include <string>

bool init();
bool loadMedia();
void close();

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Renderer *gRenderer = NULL;

LTexture gModulatedTexture;
LTexture gBackgroundTexture;

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

      Uint8 a = 255;

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_w) {
              if (a + 32 > 255) {
                a = 255;
              } else {
                a += 32;
              }
            } else if (e.key.keysym.sym == SDLK_s) {
              if (a - 32 < 0) {
                a = 0;
              } else {
                a -= 32;
              }
            }
          }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gBackgroundTexture.render(0, 0, gRenderer);

        gModulatedTexture.setAlpha(a);
        gModulatedTexture.render(0, 0, gRenderer);

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
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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
      }
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia() {
  bool success = true;

  if (!gModulatedTexture.loadFromFile("../assets/img/fadeout.png", gRenderer)) {
    printf("failed to load front texture img \n");
    success = false;
  } else {
    gModulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);
  }

  if (!gBackgroundTexture.loadFromFile("../assets/img/fadein.png", gRenderer)) {
    printf("failed to load background texture img \n");
    success = false;
  }

  return success;
}

void close() {
  gModulatedTexture.freeTexture();

  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);

  gRenderer = NULL;
  gWindow = NULL;

  IMG_Quit();
  SDL_Quit();
}
