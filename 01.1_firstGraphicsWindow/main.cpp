#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREN_HEIGHT = 480;

int main(int argc, char *argv[]) {
  SDL_Window *window = NULL;

  // the screen surface containedb by the window
  SDL_Surface *screenSurface = NULL;

  // init SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
  } else {

    // create window
    window = SDL_CreateWindow("SDL Tuturial", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("SDL could not creat a window SDL_Error: %s\n", SDL_GetError());
    } else {
      screenSurface = SDL_GetWindowSurface(window);

      SDL_FillRect(screenSurface, NULL,
                   SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));

      SDL_UpdateWindowSurface(window);

      SDL_Delay(2000);
    }
  }

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
