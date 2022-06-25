#include "LButton.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <cmath>
#include <stdio.h>
#include <string>

bool init();
bool loadMedia();
void close();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

SDL_Rect gSpriteClip[BUTTON_SPRITE_TOTAL];
LTexture gButtonTexture;
LButton gButton[TOTAL_BUTTON];

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
          for (int i = 0; 0 < TOTAL_BUTTON; i++) {
            gButton[i].handleEvent(&e);
          }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        for (int i = 0; i < TOTAL_BUTTON; i++) {
          gButton[i].render(gSpriteClip, gRenderer);
        }

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
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;

  if (!gButtonTexture.loadFromFile("../assets/img/button.png", gRenderer)) {
    success = false;
    printf("could not load button texture. error: %s", SDL_GetError());
  } else {
    for (int i = 0; i < BUTTON_SPRITE_TOTAL; i++) {
      gSpriteClip[i].x = 0;
      gSpriteClip[i].y = i * BUTTON_HEIGHT;
      gSpriteClip[i].w = BUTTON_WIDTH;
      gSpriteClip[i].h = BUTTON_HEIGHT;
      gButton[i].setTexture(&gButtonTexture);
    }
    gButton[0].setPosition(0, 0);
    gButton[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
    gButton[2].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
    gButton[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH,
                           SCREEN_HEIGHT - BUTTON_HEIGHT);
  }

  return success;
}

void close() {

  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);

  gButtonTexture.freeTexture();

  gRenderer = NULL;
  gWindow = NULL;

  IMG_Quit();
  SDL_Quit();
}
