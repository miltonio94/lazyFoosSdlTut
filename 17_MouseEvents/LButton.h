#include "LTexture.h"
#import <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <string>

enum LButtonSprite {
  BUTTON_SPRITE_MOUSE_OUT = 0,
  BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
  BUTTON_SPRITE_MOUSE_DOWN = 2,
  BUTTON_SPRITE_MOUSE_UP = 3,
  BUTTON_SPRITE_TOTAL = 4
};

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTON = 4;

class LButton {
public:
  LButton();
  ~LButton();
  void setPosition(int x, int y);
  void handleEvent(SDL_Event *e);
  void render(SDL_Rect *clip, SDL_Renderer *renderer);
  void setTexture(LTexture *texture);

private:
  LTexture *mTexture;
  SDL_Point mPosition;
  LButtonSprite mCurrentSprite;
};
