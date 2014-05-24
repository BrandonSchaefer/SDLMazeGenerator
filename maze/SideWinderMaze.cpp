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

#include "SideWinderMaze.h"

#include <stdlib.h>

using namespace std;

SideWinderMaze::SideWinderMaze(int x, int y)
  : Maze(x, y)
  , current_(2, 1)
  , i_(2)
  , j_(1)
{
  run_set_.push_back(start_.Down());

  for (int j = 1; j < Rows()-2; j++)
    OpenPassage(Point(1, j), Cell::Direction::RIGHT);
}

void SideWinderMaze::Generate()
{
  while (HasNext())
    GenerateNext();
}

void SideWinderMaze::GenerateNext()
{
  bool open_east = rand() % 2;

  if (j_ > Rows() - 2)
  {
    i_++;
    j_ = 1;

    current_ = Point(i_, 1);
  }

  j_++;

  if (open_east && InBounds(current_.Right()))
  {
    OpenPassage(current_, Cell::Direction::RIGHT);
    current_ = current_.Right();
    run_set_.push_back(current_);
  }
  else
  {
    Point up_point;

    if (run_set_.empty())
      up_point = current_;
    else
      up_point = run_set_[rand() % run_set_.size()];

    OpenPassage(up_point, Cell::Direction::UP);
    current_ = current_.Right();
    run_set_.clear();
  }
}

bool SideWinderMaze::HasNext() const
{
  return (i_ <= Columns() - 2);
}

string SideWinderMaze::GetName() const
{
  return "SideWinderMaze";
}
