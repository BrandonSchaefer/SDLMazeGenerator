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

#include "Cell.h"

namespace maze
{

Cell::Cell()
  : parent_(nullptr)
{}

void Cell::AddDirection(Direction dir)
{
  open_directions_[dir] = true;
}

void Cell::RemoveDirection(Direction dir)
{
  open_directions_[dir] = false;
}

bool Cell::Empty() const
{
  return open_directions_.none();
}

bool Cell::DirOpen(Direction const& dir) const
{
  return open_directions_[dir];
}

bool Cell::RightOpen() const
{
  return open_directions_[Direction::RIGHT];
}

bool Cell::DownOpen() const
{
  return open_directions_[Direction::DOWN];
}

bool Cell::LeftOpen() const
{
  return open_directions_[Direction::LEFT];
}

bool Cell::UpOpen() const
{
  return open_directions_[Direction::UP];
}

void Cell::SetParent(Cell::Ptr const& cell)
{
  parent_ = cell;
}

Cell::Ptr Cell::GetParent() const
{
  return parent_;
}

} // namespace maze
