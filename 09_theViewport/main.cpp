#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <cstdio>
#include <string>

bool init();
bool loadMedia();
void close();
SDL_Texture *loadTexture(std::string path);

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// TODO: Move this to the main loop!

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

        SDL_Rect topLeftViewPort = {0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport(gRenderer, &topLeftViewPort);

        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        SDL_Rect topRightViewPort = {SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2,
                                     SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport(gRenderer, &topRightViewPort);

        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        SDL_Rect bottomViewPort = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH,
                                   SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport(gRenderer, &bottomViewPort);
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

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

  gTexture = loadTexture("../assets/img/viewport.png");
  if (gTexture == NULL) {
    printf("could not load the texture");
    success = false;
  }

  return success;
}

void close() {
  SDL_DestroyTexture(gTexture);
  gTexture = NULL;

  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  IMG_Quit();
  SDL_Quit();
}
