#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class LTexture {
public:
  LTexture();
  ~LTexture();

  bool loadFromFile(std::string path, SDL_Renderer *renderer);
#if defined(SDL_TTF_MAJOR_VERSION)
  bool loadFromRenderedText(std::string textureText, SDL_Color textColour,
                            TTF_Font *font, SDL_Renderer *renderer);
#endif
  void freeTexture();
  void setColor(Uint8 red, Uint8 green, Uint8 blue);
  void setBlendMode(SDL_BlendMode blender);
  void setAlpha(Uint8 alpha);
  void render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip);
  void render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip,
              double angle, SDL_Point *center, SDL_RendererFlip flip);
  void render(int x, int y, SDL_Renderer *renderer, double angle,
              SDL_RendererFlip flip);
  void render(int x, int y, SDL_Renderer *renderer);

  int getWidth();
  int getHeight();

private:
  SDL_Texture *mTexture;

  int mWidth;
  int mHeight;
};
