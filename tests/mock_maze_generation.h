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

#include <gtest/gtest.h>

#include <maze/MazeFactory.h>
#include <maze/Solver.h>

int const WIDTH = 10;
int const HEIGHT = 11;

class MockMazeGeneration : public testing::Test
{
public:
  MockMazeGeneration()
  {}

  bool SolveAllPoints()
  {
    for (int i = 1; i <= maze->Columns()-2; i++)
    {
      for (int j = 1; j <= maze->Rows()-2; j++)
      {
        maze->SetStart(maze::Point(i,j));

        if (solver.DFSolve(maze).empty())
          return false;
      }
    }

    return true;
  }

  bool RawSolveAllPoints()
  {
    maze::RawMaze const& raw_maze = maze->GetRawMaze();

    for (int i = 1; i < (int)raw_maze.raw_maze.size(); i++)
    {
      for (int j = 1; j < (int)raw_maze.raw_maze[0].size(); j++)
      {
        maze->SetStart(maze::Point(i,j));

        if (solver.DFSolveRawMaze(raw_maze).empty())
          return false;
      }
    }

    return true;
  }

  maze::Maze::Ptr maze;
  maze::MazeFactory maze_factory;
  maze::Solver solver;
};
