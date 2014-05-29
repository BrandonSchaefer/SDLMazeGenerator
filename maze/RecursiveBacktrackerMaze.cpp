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

#include "Marked.h"
#include "RecursiveBacktrackerMaze.h"

using namespace std;

namespace maze
{

RecursiveBacktrackerMaze::RecursiveBacktrackerMaze(int x, int y)
  : Maze(x,y)
  , marked_(Columns(), Rows())
  , cell_count_((Columns()-2) * (Rows()-2) - 1)
{
  marked_.Mark(start_);
  backtracker_.push(start_);
}

void RecursiveBacktrackerMaze::Generate()
{
  while (HasNext())
    GenerateNext();
}

vector<pair<Point, Cell::Direction> > RecursiveBacktrackerMaze::GetUnMarkedNeighbours(Point& cur)
{
  vector<pair<Point, Cell::Direction> > neighbours;

  for (int i = 0; i < Cell::Direction::Size; ++i)
  {
    auto dir = Cell::Direction(i);
    if (InBounds(cur.Direction(dir)) && !marked_.IsMarked(cur.Direction(dir)))
      neighbours.push_back(make_pair(cur.Direction(dir), dir));
  }

  return neighbours;
}

void RecursiveBacktrackerMaze::GenerateNext()
{
  pair<Point, Cell::Direction> new_cur;
  vector<pair<Point, Cell::Direction> > neighbours;

  neighbours = GetUnMarkedNeighbours(current_);

  if (!neighbours.empty())
  {
    new_cur = neighbours[rand() % neighbours.size()];
    backtracker_.push(new_cur.first);
    OpenPassage(current_, new_cur.second);

    current_ = new_cur.first;
    marked_.Mark(current_);
    cell_count_--;
  }
  else if (!backtracker_.empty())
  {
    current_ = backtracker_.top();
    backtracker_.pop();

    if (HasNext())
      GenerateNext();
  }
}

bool RecursiveBacktrackerMaze::HasNext() const
{
  return cell_count_ > 0;
}

string RecursiveBacktrackerMaze::GetName() const
{
  return "RecursiveBacktrackerMaze";
}

} // namespace maze
