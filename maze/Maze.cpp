//-*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/* * Copyright (C) 2013-2014 Brandon Schaefer
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

#include "Maze.h"

#include <iostream>

using namespace std;

namespace maze
{

Maze::Maze (int width, int height)
  : start_(1, 1)
  , finish_(width, height)
  , maze_(width + 2)
{
  for (int i = 0; i < width + 2; ++i)
    for (int j = 0; j < height + 2; ++j)
      maze_[i].push_back(std::make_shared<Cell>());
}

void Maze::SetParent(Point const& current, Point const& parent)
{
  if (InBounds(current) && InBounds(parent))
    Get(current)->SetParent(Get(parent));
}

bool Maze::ParentEqualPoint(Point const& parent, Point const& point)
{
  if (InBounds(parent) && InBounds(point))
    return Get(parent)->GetParent() == Get(point);

  return false;
}

bool Maze::InBounds(Point const& pos) const
{
  int x = pos.x();
  int y = pos.y();

  if (x > 0 && y > 0 && x < (int)maze_.size() - 1 && y < (int)maze_[0].size() - 1)
    return true;

  return false;
}

Cell::Ptr Maze::Get(Point pos) const
{
  return maze_[pos.x()][pos.y()];
}

int Maze::Columns() const
{
  return maze_.size();
}

int Maze::Rows() const
{
  return maze_[0].size();
}

void Maze::OpenPassage(Point p, Cell::Direction dir)
{
  Get(p)->AddDirection(dir);
  Get(p.Direction(dir))->AddDirection(OppositeDirection(dir));
}

void Maze::SetWall(Point p, Cell::Direction dir)
{
  Get(p)->RemoveDirection(dir);
  Get(p.Direction(dir))->RemoveDirection(OppositeDirection(dir));
}

void Maze::SetStart(Point const& start)
{
  if (InBounds(start))
    start_ = start;
}

Point Maze::GetStart() const
{
  return start_;
}

Point Maze::GetFinish() const
{
  return finish_;
}

bool Maze::DirOpen(Point const& point, Cell::Direction const& dir)
{
  return (InBounds(point) && Get(point)->DirOpen(dir));
}

bool Maze::RightOpen(Point const& point)
{
  return (InBounds(point) && Get(point)->RightOpen());
}

bool Maze::DownOpen(Point const& point)
{
  return (InBounds(point) && Get(point)->DownOpen());
}

bool Maze::LeftOpen(Point const& point)
{
  return (InBounds(point) && Get(point)->LeftOpen());
}

bool Maze::UpOpen(Point const& point)
{
  return (InBounds(point) && Get(point)->UpOpen());
}

Cell::Direction Maze::GetValidRandomDirection(Point& current)
{
  vector<Cell::Direction> valid_dirs;
  Point random_dir;
  Point tmp_pt;
  int randN;

  for (int i = 0; i < Cell::Direction::Size; ++i)
  {
    tmp_pt = current.Direction(Cell::Direction(i));

    if (InBounds(tmp_pt))
      valid_dirs.push_back(Cell::Direction(i));
  }

  randN = rand() % (valid_dirs.size());

  return valid_dirs[randN];
}

Cell::Direction Maze::OppositeDirection(Cell::Direction dir) const
{
  switch (dir)
  {
    case (Cell::Direction::RIGHT):
      return Cell::Direction::LEFT;
    case (Cell::Direction::LEFT):
      return Cell::Direction::RIGHT;
    case (Cell::Direction::DOWN):
      return Cell::Direction::UP;
    case (Cell::Direction::UP):
      return Cell::Direction::DOWN;
    case (Cell::Direction::Size):
    default:
      break;
  }

  return Cell::Direction::RIGHT;
}

constexpr int raw_pos(int i) { return (i - 1) * 2; }

RawMaze Maze::GetRawMaze() const
{
  RawMaze raw_maze;
  raw_maze.start  = start_;
  raw_maze.finish = Point(finish_.x() * 2 - 1, finish_.y() * 2 - 1);

  // The size of the new raw_maze. Pretty much x * 2, (-3) because we remove -1 + -2 from the far left cells.
  int col = Columns() * 2 - 3;
  int row = Rows()    * 2 - 3;
  int n_i, n_j;

  std::vector<std::vector<int>> maze(col, std::vector<int>(row, 1));

  for (int i = 1; i < Columns() - 1; ++i)
  {
    for (int j = 1; j < Rows() - 1; ++j)
    {
      Point p(i, j);

      n_i = raw_pos(i);
      n_j = raw_pos(j);
      n_i++;
      n_j++;

      bool right = Get(p)->RightOpen();
      bool left  = Get(p)->LeftOpen();
      bool up    = Get(p)->UpOpen();
      bool down  = Get(p)->DownOpen();

      if (right || left || up || down)
        maze[n_i][n_j] = 0;

      if (right)
        maze[n_i][n_j + 1] = 0;

      if (down)
        maze[n_i + 1][n_j] = 0;
    }
  }

  raw_maze.raw_maze = maze;

  return raw_maze;
}

void Maze::PrintMaze()
{
  //cout << "\e[H";

  for (int i = 0; i < Rows(); i++)
    cout << " _";
  cout << endl;

  for (int i = 0; i < Columns(); i++)
  {
    cout << "|";
    for (int j = 0; j < Rows(); j++)
    {
      Point p(i,j);

      if (start_ == p)
        cout << "\033[4;34mS\033[0m";
      else if (finish_ == p)
        cout << "\033[4;31mF\033[0m";
      else if (Get(p)->DownOpen() && Get(p.Down())->UpOpen())
        cout << " ";
      else
        cout << "_";

      if (Get(p)->RightOpen() && Get(p.Right())->LeftOpen())
        cout << " ";
      else
        cout << "|";
    }
    cout << endl;
  }
}

} // namespace maze
