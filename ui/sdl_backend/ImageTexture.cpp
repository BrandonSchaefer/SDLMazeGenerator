#include "ImageTexture.h"

#include <SDL2/SDL_image.h>

namespace sdl_backend
{

ImageTexture::ImageTexture(SDL_Renderer* renderer)
  : renderer_(renderer)
  , texture_(nullptr)
{
}

ImageTexture::~ImageTexture()
{
  SDL_DestroyTexture(texture_);
}

SDL_Texture* ImageTexture::texture() const
{
  return texture_;
}

void ImageTexture::SetImagePath(std::string const& image_path)
{
  image_path_ = image_path;
  UpdateTexture();
}

void ImageTexture::UpdateTexture()
{
  texture_ = IMG_LoadTexture(renderer_, image_path_.c_str());
}

} // namespace sdl_backend
