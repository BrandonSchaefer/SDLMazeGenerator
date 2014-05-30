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

#include "Cell.h"

#include <sdl_backend/Color.h>

namespace sdl_maze
{

namespace
{
  SDL_Color const SPACE_COLOR  = sbe::color::WHITE;
  SDL_Color const WALL_COLOR   = sbe::color::BLACK;
  SDL_Color const MARKED_COLOR = sbe::color::GREEN;
  SDL_Color const START_COLOR  = sbe::color::BLUE;
  SDL_Color const FINISH_COLOR = sbe::color::RED;
}

Cell::Cell(SDL_Renderer* renderer)
  : color_(WALL_COLOR)
{
}

Cell::~Cell()
{
}

void Cell::Reset()
{
  color_ = WALL_COLOR;
}

void Cell::SetOpen()
{
  color_ = SPACE_COLOR;
}

void Cell::Mark()
{
  color_ = MARKED_COLOR;
}

void Cell::Start()
{
  color_ = START_COLOR;
}

void Cell::Finish()
{
  color_ = FINISH_COLOR;
}

void Cell::Update(float delta_time)
{
}

void Cell::Draw(sbe::GraphicsRenderer* graphics)
{
  graphics->SetRenderColor(color_);
  SDL_Rect dest = rect().sdl_rect();
  SDL_RenderFillRect(graphics->Renderer(), &dest);
}

} // namespace sdl_maze
