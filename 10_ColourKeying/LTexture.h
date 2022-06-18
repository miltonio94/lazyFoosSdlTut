#include <SDL2/SDL.h>
#include <string>

class LTexture {
public:
  LTexture();
  ~LTexture();

  bool loadFromFile(std::string path);

  void freeTexture();
  void render(int x, int y);

  int getWidth();
  int getHeight();

private:
  SDL_Texture *mTexture;

  int mWidth;
  int mHeight;
};
