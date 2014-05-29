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

#ifndef MAZE_GRID_CONTROLLER_H
#define MAZE_GRID_CONTROLLER_H

#include "MazeGrid.h"

#include <maze/MazeFactory.h>

#include <sdl_backend/GraphicsRenderer.h>
#include <sdl_backend/Entity.h>
#include <sdl_backend/Size.h>
#include <sdl_backend/World.h>

#include <memory>
#include <vector>

namespace sbe = sdl_backend;

namespace sdl_maze
{

class MazeGridController : public sbe::Entity
{
public:
  typedef std::shared_ptr<MazeGridController> Ptr;

  MazeGridController(unsigned id, SDL_Renderer* renderer, sbe::Size const& size);

  virtual void Update(float delta_time) override;
  virtual void UpdatePosition(sbe::World::Ptr const& world) override;
  virtual void Draw(sbe::GraphicsRenderer* graphics) override;

  /*           void  std::string maze_name */ 
  sigc::signal<void, std::string const&> maze_changed;

  std::string CurrentMazeName() const;

private:
  void CreateNewMaze();

  maze::MazeFactory maze_factory_;
  maze::MazeType current_type_;
  sbe::Size size_;
  MazeGrid maze_grid_;
};

} // namespace sdl_maze

#endif // MAZE_GRID_CONTROLLER_H
