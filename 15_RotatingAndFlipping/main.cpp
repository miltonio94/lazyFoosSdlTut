#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

bool init();
bool loadMedia();
void close();

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Renderer *gRenderer = NULL;

LTexture gArrowTexture;

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
          } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_a:
              degrees -= 60;
              break;

            case SDLK_d:
              degrees -= 60;
              break;

            case SDLK_q:
              flipType = SDL_FLIP_HORIZONTAL;
              break;

            case SDLK_w:
              flipType = SDL_FLIP_NONE;
              break;

            case SDLK_e:
              flipType = SDL_FLIP_VERTICAL;
              break;
            }
          }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gArrowTexture.render((SCREEN_WIDTH - gArrowTexture.getWidth()) / 2,
                             (SCREEN_HEIGHT - gArrowTexture.getHeight()) / 2,
                             gRenderer, degrees, flipType);

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
      }
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia() {
  bool success = true;

  if (!gArrowTexture.loadFromFile("img/arrow.png", gRenderer)) {
    printf("failed to load arrow texture img \n");
    success = false;
  }

  return success;
}

void close() {
  gArrowTexture.freeTexture();

  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);

  gRenderer = NULL;
  gWindow = NULL;

  IMG_Quit();
  SDL_Quit();
}
