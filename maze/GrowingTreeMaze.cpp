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

#include "GrowingTreeMaze.h"

namespace maze
{

GrowingTreeMaze::GrowingTreeMaze(int x, int y)
  : Maze(x,y)
  , marked_(Columns(), Rows())
  , cur_pair_(start_, Cell::Direction::RIGHT)
{
  open_neighbours_.push_back(start_);
}

void GrowingTreeMaze::SwapAndPop(int index)
{
  Point tmp_pt = open_neighbours_.back();
  open_neighbours_[index] = tmp_pt;
  open_neighbours_.pop_back();
}

// Base Case: If no more open neighbours return default values
// Recusive, If: Find a random point that has an open neighbours
//          Else: Remove from the vector, and look for a new one
std::pair<Point, Cell::Direction> GrowingTreeMaze::GetValidNeighbour()
{
  if (open_neighbours_.empty())
    return std::make_pair(Point(), Cell::Direction::RIGHT);

  int randN = rand() % open_neighbours_.size();
  std::vector<Cell::Direction> valid_dir;

  Point rand_pt = open_neighbours_[randN];
  Cell::Direction new_dir;
  Point tmp_pt;

  for (int i = 0; i < Cell::Direction::Size; ++i)
  {
    auto dir = Cell::Direction(i);
    tmp_pt = rand_pt.Direction(dir);

    if (InBounds(tmp_pt) && !marked_.IsMarked(tmp_pt))
      valid_dir.push_back(dir);
  }

  if (!valid_dir.empty())
  {
    new_dir = valid_dir[rand() % valid_dir.size()];
    open_neighbours_.push_back(rand_pt.Direction(new_dir));
    return std::make_pair(rand_pt, new_dir);
  }

  SwapAndPop(randN);

  return GetValidNeighbour();
}

void GrowingTreeMaze::Generate()
{
  while (HasNext())
    GenerateNext();
}

void GrowingTreeMaze::GenerateNext()
{
  Point cur_pt;
  Cell::Direction cur_dir;

  cur_pt  = cur_pair_.first;
  cur_dir = cur_pair_.second;

  OpenPassage(cur_pt, cur_dir);
  marked_.Mark(cur_pt.Direction(cur_dir));

  cur_pair_ = GetValidNeighbour();
}

bool GrowingTreeMaze::HasNext() const
{
  return !open_neighbours_.empty();
}

std::string GrowingTreeMaze::GetName() const
{
  return "GrowingTreeMaze";
}

} // namespace maze
