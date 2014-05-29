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
#include "Solver.h"

#include <queue>

#include <iostream>

using namespace std;

namespace maze
{

Solver::Solver()
{
}

vector<Point> Solver::DFSolve(Maze::Ptr const& maze)
{
  Point p;
  vector<Point> path;
  Point current = maze->GetStart();

  Marked marked(maze->Columns(), maze->Rows());

  path.push_back(current);
  marked.Mark(current);

  while (!path.empty())
  {
    current = path.back();

    if (maze->GetFinish() == current)
      return path;

    bool found = false;
    for (int i = 0; i < Cell::Direction::Size; ++i)
    {
      p = current.Direction(Cell::Direction(i));

      if (maze->DirOpen(current, Cell::Direction(i)) && !marked.IsMarked(p))
      {
        path.push_back(p);
        marked.Mark(p);
        found = true;
        break;
      }
    }

    if (!found)
      path.pop_back();
  }

  return path;
}

vector<Point> Solver::DFSolveRawMaze(RawMaze const& maze)
{
  vector<Point> path;
  Point current = maze.start;

  vector<vector<int>> raw_maze = maze.raw_maze;
  vector<vector<bool>> marked(raw_maze.size(), vector<bool>(raw_maze[0].size(), false));

  path.push_back(current);
  marked[current.x()][current.y()] = true;

  while (!path.empty())
  {
    current = path.back();

    if (maze.finish == current)
      return path;

    bool found = false;
    for (int i = 0; i < Cell::Direction::Size; ++i)
    {
      Point p = current.Direction(Cell::Direction(i));

      if (!raw_maze[p.x()][p.y()] && !marked[p.x()][p.y()])
      {
        path.push_back(p);
        marked[p.x()][p.y()] = true;
        found = true;
        break;
      }
    }

    if (!found)
      path.pop_back();
  }

  return path;
}

vector<Point> Solver::BFSolve(Maze::Ptr const& maze)
{
  queue<vector<Point> > paths;
  Point current = maze->GetStart();
  vector<Point> path;

  path.push_back(current);
  paths.push(path);

  vector<vector<bool> > marked(maze->Columns(), vector<bool>(maze->Rows(), false));

  while (!paths.empty())
  {
    path = paths.front();
    paths.pop();

    current = path.back();

    if (maze->GetFinish() == current)
      return path;

    if (maze->RightOpen(current) && !marked[current.Right().x()][current.Right().y()])
    {
      path.push_back(current.Right());
      paths.push(path);
      path.pop_back();
      marked[current.Right().x()][current.Right().y()] = true;
    }
    if (maze->DownOpen(current) && !marked[current.Down().x()][current.Down().y()])
    {
      path.push_back(current.Down());
      paths.push(path);
      path.pop_back();
      marked[current.Down().x()][current.Down().y()] = true;
    }
    if (maze->LeftOpen(current) && !marked[current.Left().x()][current.Left().y()])
    {
      path.push_back(current.Left());
      paths.push(path);
      path.pop_back();
      marked[current.Left().x()][current.Left().y()] = true;
    }
    if (maze->UpOpen(current) && !marked[current.Up().x()][current.Up().y()])
    {
      path.push_back(current.Up());
      paths.push(path);
      path.pop_back();
      marked[current.Up().x()][current.Up().y()] = true;
    }
  }

  return path;
}

} // namespace maze
