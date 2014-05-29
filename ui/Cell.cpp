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

#include "config.h"

#include "Cell.h"

#include <sdl_backend/Color.h>

#include <cmath>
#include <iostream>

namespace sdl_maze
{

namespace
{
  int const FONT_SIZE = 200;
  int const MAX_COLOR = 11;
  SDL_Color const DEFAULT_COLOR = {40, 40, 40, 255};
  SDL_Color const COLORS[MAX_COLOR] = {{238, 228, 218, 255},
                                       {237, 224, 200, 255},
                                       {242, 177, 121, 255},
                                       {245, 149,  99, 255},
                                       {246, 124,  95, 255},
                                       {246,  94,  59, 255},
                                       {237, 207, 114, 255},

                                       {40, 40, 40, 255},
                                       {40, 40, 40, 255},
                                       {40, 40, 40, 255},
                                       {40, 40, 40, 255}
                                      };
}

Cell::Cell(SDL_Renderer* renderer)
  : value_(0)
  , expand_(0)
  , total_(0.0f)
  , value_texture_(renderer)
{
  value_texture_.SetFontSize(FONT_SIZE);
  value_texture_.SetText("");
}

Cell::~Cell()
{
}

bool Cell::Open() const
{
  return value_ == 0;
}

int Cell::Value() const
{
  return value_;
}


void Cell::SetValue(int value)
{
  value_ = value;

  value_texture_.SetText(std::to_string(value_));
}

void Cell::Reset()
{
  value_ = 0;
  value_texture_.SetText("");
}

void Cell::Increment()
{
  if (value_ == 0)
    value_ = 2;
  else
    value_ *= 2;

  value_texture_.SetText(std::to_string(value_));
}

void Cell::PieceCombined()
{
  expand_ = 3;
}

void Cell::Update(float delta_time)
{
  if (expand_ > 0 && total_ > 0.1f)
  {
    expand_--;
    total_ = 0.0f;
  }

  total_ += delta_time;
}

void Cell::Draw(sbe::GraphicsRenderer* graphics)
{
  sbe::Rect cpy_rect = rect();
  cpy_rect.Shrink(10);
  cpy_rect.Expand(expand_*5);
  dest = cpy_rect.sdl_rect();

  SDL_RenderFillRect(graphics->Renderer(), &dest);

  cpy_rect.Shrink(20);
  dest = cpy_rect.sdl_rect();
  SDL_RenderCopy(graphics->Renderer(), value_texture_.texture(), nullptr, &dest);
}

} // namespace sdl_maze
