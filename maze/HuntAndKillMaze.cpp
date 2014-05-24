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

/* FIXME This maze does not work correctly, produces infinte loops (which is shouldnt) 
   need to re-do this implemention... sad face
*/
#include "HuntAndKillMaze.h"

HuntAndKillMaze::HuntAndKillMaze(int x, int y)
  : Maze(x, y)
  , marked_(Columns(), Rows())
  , last_used_index_(start_.x(), start_.y())
  , current_(last_used_index_)
{
  marked_.Mark(start_);
}

bool HuntAndKillMaze::HasOpenNeighbours(Point& current)
{
  Point cur_dir;
  for (auto dir : directions_)
  {
    cur_dir = current.Direction(dir);

    if (InBounds(cur_dir) && !marked_.IsMarked(cur_dir))
      return true;
  }

  return false;
}

void HuntAndKillMaze::Generate()
{
  while (HasNext())
    GenerateNext();
}

void HuntAndKillMaze::GenerateNext()
{
  Cell::Direction random_dir;

  if (HasOpenNeighbours(current_))
  {
    random_dir = GetUnMarkedRandomDirection(current_);
    OpenPassage(current_, random_dir);

    marked_.Mark(current_);
    current_ = current_.Direction(random_dir);
  }
  else
  {
    last_used_index_ = FindNextUnMarkedCell(last_used_index_);
    current_ = last_used_index_;
  }
}

bool HuntAndKillMaze::HasNext() const
{
  return last_used_index_.x() != -1;
}

Point HuntAndKillMaze::FindNextUnMarkedCell(Point const& current)
{
  for (int i = current.x(); i < Columns()-1; i++)
  {
    for (int j = 1; j < Rows()-1; j++)
    {
      for (auto d : directions_)
      {
        Point p(i,j);
        Point tmp = Point(i,j).Direction(d);

        if (!marked_.IsMarked(p) && InBounds(p) && marked_.IsMarked(tmp))
        {
          OpenPassage(p, d);
          marked_.Mark(p);

          return p;
        }
      }
    }
  }

  return {-1,-1};
}

Cell::Direction HuntAndKillMaze::GetUnMarkedRandomDirection(Point& current)
{
  std::vector<Cell::Direction> valid_dirs;
  Point random_dir;
  Point tmp_pt;
  int randN;

  for (auto dir : directions_)
  {
    tmp_pt = current.Direction(dir);

    if (InBounds(tmp_pt) && !marked_.IsMarked(tmp_pt))
      valid_dirs.push_back(dir);
  }

  randN = rand() % (valid_dirs.size());

  return valid_dirs[randN];
}

std::string HuntAndKillMaze::GetName() const
{
  return "HuntAndKillMaze";
}
