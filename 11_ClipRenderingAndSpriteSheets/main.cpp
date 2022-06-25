#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <cstdio>
#include <string>

bool init();
bool loadMedia();
void close();
SDL_Texture *loadTexture(std::string path);

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Renderer *gRenderer = NULL;

SDL_Rect gSpriteClips[4];
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

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gSpriteSheetTexture.render(0, 0, gRenderer, &gSpriteClips[0]);

        gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[1].w, 0,
                                   gRenderer, &gSpriteClips[1]);

        gSpriteSheetTexture.render(0, SCREEN_HEIGHT - gSpriteClips[2].h,
                                   gRenderer, &gSpriteClips[2]);

        gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[3].w,
                                   SCREEN_HEIGHT - gSpriteClips[3].h, gRenderer,
                                   &gSpriteClips[3]);

        SDL_RenderPresent(gRenderer);
      }
    }
  }
  close();
  return 0;
}

SDL_Texture *loadTexture(std::string path) {
  SDL_Texture *newTexture = NULL;
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());

  if (loadedSurface == NULL) {
    printf("Failed to load image %s! Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to transform surface %s into a texture! SDL Error: %s \n",
             path.c_str(), SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
  }
  return newTexture;
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

  return true;
}

bool loadMedia() {
  bool success = true;

  if (!gSpriteSheetTexture.loadFromFile("../assets/img/dots.png", gRenderer)) {
    printf("failed to load dots texture img \n");
    success = false;
  } else {
    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 100;
    gSpriteClips[0].h = 100;

    gSpriteClips[1].x = 100;
    gSpriteClips[1].y = 0;
    gSpriteClips[1].w = 100;
    gSpriteClips[1].h = 100;

    gSpriteClips[2].x = 0;
    gSpriteClips[2].y = 100;
    gSpriteClips[2].w = 100;
    gSpriteClips[2].h = 100;

    gSpriteClips[3].x = 100;
    gSpriteClips[3].y = 100;
    gSpriteClips[3].w = 100;
    gSpriteClips[3].h = 100;
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
