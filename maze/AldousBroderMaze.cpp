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

#include "AldousBroderMaze.h"

AldousBroderMaze::AldousBroderMaze(int x, int y)
  : Maze(x,y)
  , marked_(Columns(), Rows())
  , current_(1, 1)
  , cell_count_((Columns()-2) * (Rows()-2))
{}

void AldousBroderMaze::Generate()
{
  while (HasNext())
    GenerateNext();
}

void AldousBroderMaze::GenerateNext()
{
  Cell::Direction rand_dir = GetValidRandomDirection(current_);
  current_ = current_.Direction(rand_dir);

  if (!marked_.IsMarked(current_))
  {
    OpenPassage(current_, OppositeDirection(rand_dir));
    marked_.Mark(current_);
    cell_count_--;
  }
  else
  {
    // If we don't open a new passage, keep going until we do.
    GenerateNext();
  }
}

bool AldousBroderMaze::HasNext() const
{
  return cell_count_ > 0;
}

std::string AldousBroderMaze::GetName() const
{
  return "AldousBroderMaze";
}
