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

#include "MazeGrid.h"

#include <sdl_backend/Color.h>
#include <sdl_backend/GraphicsRenderer.h>

namespace sdl_maze
{

namespace
{
  int const SPACING          = 0;
  int const GENERATION_SPEED = 5;
}

MazeGrid::MazeGrid(SDL_Renderer* renderer, maze::Maze::Ptr const& maze)
  : size_(0, 0)
  , current_maze_(maze)
  , gen_speed_(GENERATION_SPEED)
{
  maze::RawMaze raw_maze = current_maze_->GetRawMaze();
  size_.width  = raw_maze.raw_maze.size();
  size_.height = raw_maze.raw_maze[0].size();

  grid_.resize(size_.width);

  for (int i = 0; i < size_.width; ++i)
    for (int j = 0; j < size_.height; ++j)
      grid_[i].push_back(std::make_shared<Cell>(renderer));
}

void MazeGrid::TranslateMazeToGridView()
{
  maze::RawMaze raw_maze = current_maze_->GetRawMaze();

  for (unsigned i = 0; i < raw_maze.raw_maze.size(); ++i)
    for (unsigned j = 0; j < raw_maze.raw_maze[0].size(); ++j)
      if (!raw_maze.raw_maze[i][j])
        grid_[i][j]->SetOpen();

  grid_[raw_maze.start.x() ][raw_maze.start.y()]->Start();
  grid_[raw_maze.finish.x()][raw_maze.finish.y()]->Finish();
}

void MazeGrid::SetNewMaze(maze::Maze::Ptr const& maze)
{
  current_maze_ = maze;
  TranslateMazeToGridView();
}

void MazeGrid::FinishGeneration()
{
  current_maze_->Generate();
  TranslateMazeToGridView();
}

void MazeGrid::SolveMaze()
{
  if (!current_maze_->HasNext())
  {
    //FIXME should hold on to this... when we translate, possibly
    maze::RawMaze raw_maze = current_maze_->GetRawMaze();

    std::vector<maze::Point> points = solver_.DFSolveRawMaze(raw_maze);

    for (auto const& p : points)
      grid_[p.x()][p.y()]->Mark();

    grid_[raw_maze.start.x() ][raw_maze.start.y()]->Start();
    grid_[raw_maze.finish.x()][raw_maze.finish.y()]->Finish();
  }
}

void MazeGrid::UpdateCellGeometry()
{
  int start_x = x() / 2;
  int start_y = y() / 2;

  int w = width()  / size_.width;
  int h = (height() - y()) / size_.height;

  int min_size = std::min(w, h);

  // Need to center the grid
  int grid_size_w = min_size * size_.width;
  int grid_size_h = min_size * size_.height;

  start_x += width()  / 2 - grid_size_w / 2;
  start_y += height() / 2 - grid_size_h / 2;

  for (int i = 0; i < size_.width; ++i)
  {
    for (int j = 0; j < size_.height; ++j)
    {
      grid_[i][j]->SetRect({start_x + i * (min_size + SPACING),
                            start_y + j * (min_size + SPACING),
                            min_size, min_size});
    }
  }
}

void MazeGrid::IncreaseGenSpeed()
{
  gen_speed_++;
}

void MazeGrid::DecreaseGenSpeed()
{
  if (gen_speed_ - 1 > 0)
    gen_speed_--;
}

std::string MazeGrid::CurrentMazeName() const
{
  if (current_maze_)
    return current_maze_->GetName();

  return "<NoMaze>";
}

bool MazeGrid::InBounds(sbe::Point const& point) const
{
  if (point.x >= 0 && point.x < size_.width &&
      point.y >= 0 && point.y < size_.height)
  {
    return true;
  }

  return false;
}

void MazeGrid::Clear()
{
  for (int i = 0; i < size_.width; ++i)
    for (int j = 0; j < size_.height; ++j)
      grid_[i][j]->Reset();
}

void MazeGrid::Update(float delta_time)
{
  if (current_maze_->HasNext())
  {
    for (int i = 0; i < gen_speed_; ++i)
      if (current_maze_->HasNext())
        current_maze_->GenerateNext();

    TranslateMazeToGridView();
  }

  for (int i = 0; i < size_.width; ++i)
    for (int j = 0; j < size_.height; ++j)
      grid_[i][j]->Update(delta_time);
}

void MazeGrid::Draw(sbe::GraphicsRenderer* graphics)
{
  for (int i = 0; i < size_.width; ++i)
    for (int j = 0; j < size_.height; ++j)
      grid_[i][j]->Draw(graphics);
}

} // namespace sdl_maze
