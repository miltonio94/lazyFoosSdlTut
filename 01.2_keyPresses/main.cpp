#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

// enum KeyPressSurface {
//   KEY_PRESS_SURFACE_DEFAULT,
//   KEY_PRESS_SURFACE_UP,
//   KEY_PRESS_SURFACE_RIGHT,
//   KEY_PRESS_SURFACE_DOWN,
//   KEY_PRESS_SURFACE_LEFT,
//   KEY_PRESS_SURFACE_TOTAL
// };

// bool init();
// bool loadMedia();
// void close();
// SDL_Surface *loadSurface(std::string path);

// SDL_Window *gWindow = NULL;
// SDL_Surface *gScreenSurface = NULL;
// SDL_Surface *gKeyPressSurface[KEY_PRESS_SURFACE_TOTAL];
// SDL_Surface *gCurrentSurface = NULL;

// const int SCREEN_WIDTH = 640;
// const int SCREN_HEIGHT = 480;

// int main(int argc, char *argv[]) {
//   SDL_Window *window = NULL;

//   // the screen surface containedb by the window
//   SDL_Surface *screenSurface = NULL;

//   // init SDL
//   if (!init()) {
//     printf("Failed to initialize");
//   } else {
//     if (!loadMedia()) {
//       printf("Failed to load meadia");
//     } else {
//       bool quit = false;
//       SDL_Event e;
//       gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];

//       while (!quit) {
//         while (SDL_PollEvent(&e) != 0) {
//           if (e.type == SDL_QUIT) {
//             quit = true;
//           } else if (e.type == SDL_KEYDOWN) {
//             switch (e.key.keysym.sym) {
//             case SDLK_DOWN:
//               gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
//               break;

//             case SDLK_RIGHT:
//               gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
//               break;

//             case SDLK_LEFT:
//               gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
//               break;

//             case SDLK_UP:
//               gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
//               break;
//               gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
//               break;
//             }
//           }
//         }
//         SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
//         SDL_UpdateWindowSurface(gWindow);
//       }
//     }
//   }
//   close();
//   return 0;
// }

// SDL_Surface *loadSurface(std::string path) {
//   SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
//   if (loadedSurface == NULL) {
//     printf("Failed to load image %s! Error: \n%s\n", path.c_str(),
//            SDL_GetError());
//   }
//   return loadedSurface;
// }

// bool init() {
//   bool success = true;
//   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//     printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
//     success = false;
//   } else {
//     gWindow = SDL_CreateWindow("SDL Tuturial", SDL_WINDOWPOS_UNDEFINED,
//                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
//                                SCREN_HEIGHT, SDL_WINDOW_SHOWN);
//     if (gWindow == NULL) {
//       printf("SDL could not creat a window SDL_Error: %s\n", SDL_GetError());
//       success = false;
//     } else {
//       gScreenSurface = SDL_GetWindowSurface(gWindow);
//     }
//   }

//   return true;
// }

// bool loadMedia() {
//   bool success = true;

//   gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
//   if (gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
//     printf("failed to load default image! \n");
//     success = false;
//   }

//   gKeyPressSurface[KEY_PRESS_SURFACE_UP] = loadSurface("down.bmp");
//   if (gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] == NULL) {
//     printf("failed to load down image! \n");
//     success = false;
//   }

//   gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
//   if (gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] == NULL) {
//     printf("failed to load right image! \n");
//     success = false;
//   }

//   gKeyPressSurface[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
//   if (gKeyPressSurface[KEY_PRESS_SURFACE_UP] == NULL) {
//     printf("failed to load up image! \n");
//     success = false;
//   }

//   gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
//   if (gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == NULL) {
//     printf("failed to load left image! \n");
//     success = false;
//   }

//   return success;
// }

// void close() {
//   for (int i; i < KEY_PRESS_SURFACE_TOTAL; i++) {
//     SDL_FreeSurface(gKeyPressSurface[i]);
//     gKeyPressSurface[i] = NULL;
//   }

//   SDL_DestroyWindow(gWindow);
//   gWindow = NULL;

//   SDL_Quit();
// }
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Key press surfaces constants
enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Loads individual image
SDL_Surface *loadSurface(std::string path);

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The images that correspond to a keypress
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// Current displayed image
SDL_Surface *gCurrentSurface = NULL;

bool init() {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Get window surface
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia() {
  // Loading success flag
  bool success = true;

  // Load default surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("hello_world.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("Failed to load default image!\n");
    success = false;
  }

  // Load up surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    printf("Failed to load up image!\n");
    success = false;
  }

  // Load down surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    printf("Failed to load down image!\n");
    success = false;
  }

  // Load left surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
    printf("Failed to load left image!\n");
    success = false;
  }

  // Load right surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    printf("Failed to load right image!\n");
    success = false;
  }

  return success;
}

void close() {
  // Deallocate surfaces
  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
    SDL_FreeSurface(gKeyPressSurfaces[i]);
    gKeyPressSurfaces[i] = NULL;
  }

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

SDL_Surface *loadSurface(std::string path) {
  // Load image at specified path
  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path.c_str(),
           SDL_GetError());
  }

  return loadedSurface;
}

int main(int argc, char *args[]) {
  // Start up SDL and create window
  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    // Load media
    if (!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
      // Main loop flag
      bool quit = false;

      // Event handler
      SDL_Event e;

      // Set default current surface
      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

      // While application is running
      while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
          // User requests quit
          if (e.type == SDL_QUIT) {
            quit = true;
          }
          // User presses a key
          else if (e.type == SDL_KEYDOWN) {
            // Select surfaces based on key press
            switch (e.key.keysym.sym) {
            case SDLK_UP:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
              break;

            case SDLK_DOWN:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
              break;

            case SDLK_LEFT:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
              break;

            case SDLK_RIGHT:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
              break;

            default:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
              break;
            }
          }

          SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
          // Update the surface
          SDL_UpdateWindowSurface(gWindow);

          SDL_Delay(2000);
        }

        // Apply the current image
        SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
        // Update the surface
        SDL_UpdateWindowSurface(gWindow);

        SDL_Delay(2000);
      }
    }
  }

  // Free resources and close SDL
  close();

  return 0;
}
