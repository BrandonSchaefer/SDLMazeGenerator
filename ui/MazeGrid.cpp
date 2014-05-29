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
  int const SPACING = 1;
  int const PERCENT = 10;
}

MazeGrid::MazeGrid(SDL_Renderer* renderer, sbe::Size const& size)
  : size_(size)
  , grid_(size_.width)
{
  for (int i = 0; i < size_.width; ++i)
    for (int j = 0; j < size.height; ++j)
      grid_[i].push_back(std::make_shared<Cell>(renderer));
}

void MazeGrid::UpdateCellGeometry()
{
  int start_x = x();
  int start_y = y();

  int w = (width()  - start_x) / size_.width;
  int h = (height() - start_y) / size_.height;

  int min_size = std::min(w, h);

  // Need to center the grid
  int grid_size = (min_size + SPACING) * size_.width;
  start_x += width()  / 2 - grid_size / 2;
  start_y += height() / 2 - grid_size / 2; 

  for (int i = 0; i < size_.width; ++i)
  {
    for (int j = 0; j < size_.height; ++j)
    {
      grid_[i][j]->SetRect({i * (min_size + SPACING) + start_x,
                            j * (min_size + SPACING) + start_y,
                            min_size, min_size});
    }
  }

}

std::vector<sbe::Point> MazeGrid::GetPointsToCheckFromDirection(sbe::Direction const& direction)
{
  std::vector<sbe::Point> points;

  switch (direction)
  {
    case sbe::Direction::RIGHT:
      points = GetRightPoints();
      break;
    case sbe::Direction::UP:
      points = GetUpPoints();
      break;
    case sbe::Direction::DOWN:
      points = GetDownPoints();
      break;
    case sbe::Direction::LEFT:
      points = GetLeftPoints();
      break;
    default:
      break;
  }

  return points;
}

std::vector<sbe::Point> MazeGrid::GetRightPoints() const
{
  std::vector<sbe::Point> points;

  for (int i = size_.width - 2; i >= 0; --i)
    for (int j = size_.height - 1; j >= 0; --j)
      points.push_back({i, j});

  return points;
}

std::vector<sbe::Point> MazeGrid::GetUpPoints() const
{
  std::vector<sbe::Point> points;

  for (int i = 1; i < size_.width; ++i)
    for (int j = 0; j < size_.height; ++j)
      points.push_back({j, i});

  return points;
}

std::vector<sbe::Point> MazeGrid::GetDownPoints() const
{
  std::vector<sbe::Point> points;

  for (int i = size_.height - 2; i >= 0; --i)
    for (int j = 0; j < size_.width; ++j)
      points.push_back({j, i});

  return points;
}

std::vector<sbe::Point> MazeGrid::GetLeftPoints() const
{
  std::vector<sbe::Point> points;

  for (int i = 1; i < size_.width; ++i)
    for (int j = 0; j < size_.height; ++j)
      points.push_back({i, j});

  return points;
}


bool MazeGrid::CanAnyCellMove() const
{
  for (int i = 0; i < size_.width; ++i)
  {
    for (int j = 0; j < size_.height; ++j)
    {
      if (grid_[i][j]->Open())
        return true;

      if (NeighbourSharesValue({i, j}))
        return true;
    }
  }

  return false;
}

bool MazeGrid::NeighbourSharesValue(sbe::Point const& pos) const
{
  int value = Value(pos);

  if (value <= 0)
    return false;

  for (unsigned i = 0; i < (unsigned)sbe::Direction::Size; ++i)
  {
    sbe::Point new_point = pos.MoveDir(sbe::Direction(i));
    if (InBounds(new_point) && Value(new_point) == value)
      return true;
  }

  return false;
}

void MazeGrid::AddRandomPiece()
{
  std::vector<sbe::Point> open_spaces;

  for (int i = 0; i < size_.width; ++i)
    for (int j = 0; j < size_.height; ++j)
      if (grid_[i][j]->Open())
        open_spaces.push_back({i, j});

  if (!open_spaces.empty())
  {
    sbe::Point rand_open_space = open_spaces[rand() % open_spaces.size()];
    grid_[rand_open_space.x][rand_open_space.y]->Increment();

    int random_percent = rand() % 100;

    if (random_percent < PERCENT)
      grid_[rand_open_space.x][rand_open_space.y]->Increment();
  }
}

int MazeGrid::Value(sbe::Point const& point) const
{
  if (InBounds(point))
    return grid_[point.x][point.y]->Value();

  return 0;
}

bool MazeGrid::Open(sbe::Point const& point) const
{
  return (InBounds(point) && grid_[point.x][point.y]->Open());
}

void MazeGrid::Increment(sbe::Point const& point)
{
  if (InBounds(point))
    grid_[point.x][point.y]->Increment();
}

void MazeGrid::Reset(sbe::Point const& point)
{
  if (InBounds(point))
    grid_[point.x][point.y]->Reset();
}

void MazeGrid::SwapCells(sbe::Point const& start, sbe::Point const& dest)
{
  if (InBounds(start) && InBounds(dest))
  {
    grid_[dest.x][dest.y]->SetValue(grid_[start.x][start.y]->Value());
    grid_[start.x][start.y]->Reset();
  }
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

void MazeGrid::PieceCombined(sbe::Point const& pos)
{
  grid_[pos.x][pos.y]->PieceCombined();
}

void MazeGrid::Update(float delta_time)
{
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
