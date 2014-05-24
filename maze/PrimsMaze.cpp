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

#include "PrimsMaze.h"

PrimsMaze::PrimsMaze(int x, int y)
  : Maze(x,y)
  , marked_(Columns(), Rows())
  , current_((Columns()-2)/2, (Rows()-2)/2)
{
  SetParent(current_, start_);
  marked_.Mark(current_);
  OpenPassage(current_, Cell::Direction::RIGHT);
  walls_.push_back(current_.Right());
}

Cell::Direction PrimsMaze::GetOppositeParentsDirection(Point const& current)
{
  if (ParentEqualPoint(current, current.Right()))
    return Cell::Direction::LEFT;
  else if (ParentEqualPoint(current, current.Down()))
    return Cell::Direction::UP;
  else if (ParentEqualPoint(current, current.Left()))
    return Cell::Direction::RIGHT;
  else
    return Cell::Direction::DOWN;
}

void PrimsMaze::Generate()
{
  while (HasNext())
    GenerateNext();
}

void PrimsMaze::GenerateNext()
{
  int randN;
  Point opp_cur;
  Cell::Direction opp_dir;

  current_ = walls_.back();
  walls_.pop_back();

  opp_dir = GetOppositeParentsDirection(current_);
  opp_cur = current_.Direction(opp_dir);

  if (!marked_.IsMarked(current_))
  {
    OpenPassage(current_, OppositeDirection(opp_dir));
    marked_.Mark(current_);

    for (auto dir : directions_)
    {
      Point cur_dir = current_.Direction(dir);

      if (!InBounds(cur_dir) || marked_.IsMarked(cur_dir))
        continue;

      SetParent(cur_dir, current_);
      walls_.push_back(cur_dir);

      randN = rand() % walls_.size();
      Point tmp = walls_[randN];
      walls_[randN] = walls_.back();
      walls_[walls_.size()-1] = tmp;
    }
  }
}

bool PrimsMaze::HasNext() const
{
  return !walls_.empty();
}

std::string PrimsMaze::GetName() const
{
  return "PrimsMaze";
}
