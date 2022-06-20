#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <string>

class LTexture {
public:
  LTexture();
  ~LTexture();

  bool loadFromFile(std::string path, SDL_Renderer *renderer);

  void freeTexture();
  void render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip);
  void render(int x, int y, SDL_Renderer *renderer);

  int getWidth();
  int getHeight();

private:
  SDL_Texture *mTexture;

  int mWidth;
  int mHeight;
};
