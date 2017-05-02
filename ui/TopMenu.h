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

#ifndef TOP_MENU_H
#define TOP_MENU_H

#include <sdl_backend/Entity.h>
#include <sdl_backend/StringTexture.h>
#include <sdl_backend/World.h>

namespace sbe = sdl_backend;

namespace sdl_maze
{

class TopMenu : public sbe::Entity
{
public:
  typedef std::shared_ptr<TopMenu> Ptr;

  TopMenu(unsigned id, SDL_Renderer* renderer);

  void UpdatePosition(sbe::World::Ptr const& world);
  void Update(float delta_time);
  void Draw(sbe::GraphicsRenderer* graphics);

  void SetCurrentMazeName(std::string const& maze_name);

private:
  sbe::StringTexture maze_name_texture_;

};

} // namespace sdl_maze

#endif // TOP_MENU_H
