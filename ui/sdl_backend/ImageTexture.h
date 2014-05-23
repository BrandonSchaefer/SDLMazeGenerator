// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/*
 * Copyright (C) 2014 Brandon Schaefer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Brandon Schaefer <brandontschaefer@gmail.com>
 */

#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include <SDL2/SDL.h>

#include <string>

namespace sdl_backend
{

class ImageTexture
{
public:
  ImageTexture(SDL_Renderer* renderer);
  ~ImageTexture();

  SDL_Texture* texture() const;

  void SetImagePath(std::string const& image_path);

private:
  void UpdateTexture();

  SDL_Renderer* renderer_;
  SDL_Texture* texture_;

  std::string image_path_;

};

} // namespace sdl_backend

#endif // IMAGE_TEXTURE_H
