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

const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
LTexture gSpriteSheetTexture;

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
      int frame = 0;

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        SDL_Rect *currentClip = &gSpriteClips[frame / 4];
        gSpriteSheetTexture.render((SCREEN_WIDTH - currentClip->w) / 2,
                                   (SCREEN_HEIGHT - currentClip->h) / 2,
                                   gRenderer, currentClip);

        SDL_RenderPresent(gRenderer);

        ++frame;
        if (frame / 4 >= WALKING_ANIMATION_FRAMES) {
          frame = 0;
        }
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
      }
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia() {
  bool success = true;

  if (!gSpriteSheetTexture.loadFromFile("../assets/img/foo.png", gRenderer)) {
    printf("failed to load foo walking texture img \n");
    success = false;
  } else {
    for (int i = 0; i < 4; i++) {
      gSpriteClips[i].x = i * 64;
      gSpriteClips[i].y = 0;
      gSpriteClips[i].w = 64;
      gSpriteClips[i].h = 205;
    }
  }

  return success;
}

void close() {
  gSpriteSheetTexture.freeTexture();

  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);

  gRenderer = NULL;
  gWindow = NULL;

  IMG_Quit();
  SDL_Quit();
}
