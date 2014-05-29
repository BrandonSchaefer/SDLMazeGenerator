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

#include "WilsonsMaze.h"

namespace maze
{

WilsonsMaze::WilsonsMaze(int x, int y)
  : Maze(x,y)
  , marked_(Columns(), Rows())
  , paths_(Columns(), std::vector<Cell::Direction>(Rows(), Cell::Direction::RIGHT))
{
  for (int i = 1; i < (Columns() - 1); i++)
    for (int j = 1; j < (Rows() - 1); j++)
      outside_cells_.push_back(Point(i,j));

  marked_.Mark(start_);
}

Point GetRandomValidPoint(std::vector<Point>& outside_cells)
{
  int randN = rand() % outside_cells.size();

  Point tmp = outside_cells[randN];
  outside_cells[randN] = outside_cells[outside_cells.size()-1];
  outside_cells.pop_back();

  return tmp;
}

void WilsonsMaze::Generate()
{
  while (HasNext())
    GenerateNext();
}

void WilsonsMaze::GenerateNext()
{
  Point random_pt;
  Point walker;

  Cell::Direction random_dir;

  random_pt = GetRandomValidPoint(outside_cells_);
  walker = random_pt;

  while (!marked_.IsMarked(walker))
  {
    random_dir = GetValidRandomDirection(walker);
    paths_[walker.x()][walker.y()] = random_dir;
    walker = walker.Direction(random_dir);
  }

  while (!marked_.IsMarked(random_pt))
  {
    OpenPassage(random_pt, paths_[random_pt.x()][random_pt.y()]);
    marked_.Mark(random_pt);

    random_pt = random_pt.Direction(paths_[random_pt.x()][random_pt.y()]);
  }
}

bool WilsonsMaze::HasNext() const
{
  return !outside_cells_.empty();
}

std::string WilsonsMaze::GetName() const
{
  return "WilsonsMaze";
}

} // namespace maze
