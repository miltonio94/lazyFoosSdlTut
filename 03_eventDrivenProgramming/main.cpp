#include <SDL2/SDL.h>
// #include <SDL2/SDL_events.h>
// #include <SDL2/SDL_surface.h>
// #include <SDL2/SDL_video.h>
#include <stdio.h>

bool init();
bool loadMedia();
void close();

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gXOut = NULL;

const int SCREEN_WIDTH = 640;
const int SCREN_HEIGHT = 480;

int main(int argc, char *argv[]) {
  SDL_Window *window = NULL;

  // the screen surface containedb by the window
  SDL_Surface *screenSurface = NULL;

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
        SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);
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
                               SCREN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("SDL could not creat a window SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return true;
}

bool loadMedia() {
  bool success = true;

  gXOut = SDL_LoadBMP("x.bmp");
  if (gXOut == NULL) {
    printf("SDL could not load image SDL_Error: %s\n", SDL_GetError());
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(gXOut);
  gXOut = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}
