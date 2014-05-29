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

#include "TopMenu.h"

#include <sdl_backend/Color.h>
#include <sdl_backend/StringTextureData.h>

namespace sdl_maze
{

namespace
{
  int const FONT_SIZE = 30;
}

TopMenu::TopMenu(unsigned id, SDL_Renderer* renderer)
  : Entity(id)
  , maze_name_texture_(renderer)
{
  maze_name_texture_.SetFontSize(FONT_SIZE);
  maze_name_texture_.SetText("Testing!");
}

void TopMenu::UpdatePosition(sbe::World::Ptr const& world)
{
}

void TopMenu::Update(float delta_time)
{
}

void TopMenu::Draw(sbe::GraphicsRenderer* graphics)
{
  sbe::Rect const& name = maze_name_texture_.GetRect();
  SDL_Rect dest = sdl_rect();
  dest.x = dest.w / 2 - name.width() / 2;
  dest.w = name.width();

  SDL_RenderCopy(graphics->Renderer(), maze_name_texture_.texture(), nullptr, &dest);
}

void TopMenu::SetCurrentMazeName(std::string const& maze_name)
{
  maze_name_texture_.SetText(maze_name);
}

} // namespace sdl_maze
