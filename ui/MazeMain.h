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

#ifndef MAZE_MAIN_H
#define MAZE_MAIN_H

#include <sdl_backend/Entity.h>
#include <sdl_backend/EntityLayer.h>
#include <sdl_backend/ImageTexture.h>
#include <sdl_backend/MainLoop.h>

namespace sbe = sdl_backend;

namespace sdl_maze
{

class MazeMain : public sbe::Entity
{
public:
  typedef std::shared_ptr<MazeMain> Ptr;

  MazeMain(unsigned id, sbe::MainLoop::Ptr const& main_loop);
  ~MazeMain();

  void UpdatePosition(sbe::World::Ptr const& world) override;
  void Update(float delta_time) override;
  void Draw(sbe::GraphicsRenderer* graphics) override;

private:
  sbe::MainLoop::Ptr main_loop_;
  sbe::EntityLayer::Ptr game_layer_;
};

} // namespace sdl_maze

#endif // MAZE_MAIN_H
