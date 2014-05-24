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

#include "BinaryTreeMaze.h"

#include <stdlib.h>

using namespace std;

BinaryTreeMaze::BinaryTreeMaze(int x, int y)
  : Maze(x,y)
  , i_(1)
  , j_(1)
{}

void BinaryTreeMaze::Generate()
{
  while (HasNext())
    GenerateNext();
}

void BinaryTreeMaze::GenerateNext()
{
  bool move_up = rand() % 2;
  Point p;

  if (j_ >= Rows() - 1)
  {
    i_++;
    j_ = 1;
  }

  p = Point(i_, j_);
  j_++;

  if (move_up)
  {
    if (InBounds(p.Up()))
      OpenPassage(p, Cell::Direction::UP);
    else if (InBounds(p.Left()))
      OpenPassage(p, Cell::Direction::LEFT);
  }
  else
  {
    if (InBounds(p.Left()))
      OpenPassage(p, Cell::Direction::LEFT);
    else if (InBounds(p.Up()))
      OpenPassage(p, Cell::Direction::UP);
  }
}

bool BinaryTreeMaze::HasNext() const
{
  return (i_ < Columns() - 1);
}

string BinaryTreeMaze::GetName() const
{
  return "BinaryTreeMaze";
}
