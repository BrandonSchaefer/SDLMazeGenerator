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

#ifndef MAZE_GRID_H
#define MAZE_GRID_H

#include "Cell.h"

#include <maze/Maze.h>
#include <maze/Solver.h>

#include <sdl_backend/GraphicsRenderer.h>
#include <sdl_backend/RenderableGeometry.h>
#include <sdl_backend/Size.h>

#include <memory>
#include <vector>

namespace sbe = sdl_backend;

namespace sdl_maze
{

class MazeGrid : public sbe::RenderableGeometry
{
public:
  MazeGrid(SDL_Renderer* renderer, maze::Maze::Ptr const& maze);

  void UpdateCellGeometry();
  void Clear();

  void SetNewMaze(maze::Maze::Ptr const& maze);

  bool InBounds(sbe::Point const& point) const;

  virtual void Update(float delta_time) override;
  virtual void Draw(sbe::GraphicsRenderer* graphics) override;

  std::string CurrentMazeName() const;

  void FinishGeneration();
  void SolveMaze();

  void IncreaseGenSpeed();
  void DecreaseGenSpeed();

private:
  void TranslateMazeToGridView();

  sbe::Size size_;
  maze::Maze::Ptr current_maze_;
  std::vector<std::vector<Cell::Ptr>> grid_;
  maze::Solver solver_;

  int gen_speed_;
};

} // namespace sdl_maze

#endif // MAZE_GRID_H
