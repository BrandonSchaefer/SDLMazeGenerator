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

#include "MazeFactory.h"

#include "AldousBroderMaze.h"
#include "BinaryTreeMaze.h"
#include "GrowingTreeMaze.h"
#include "HuntAndKillMaze.h"
#include "PrimsMaze.h"
#include "RecursiveBacktrackerMaze.h"
#include "SideWinderMaze.h"
#include "WilsonsMaze.h"

namespace maze
{

MazeFactory::MazeFactory()
{}

std::string MazeFactory::GetMazeTitle(MazeType maze_type)
{
  switch(maze_type)
  {
    case(ALDOUS_BRODER):
      return "AldousBroderMaze";
    case(BINARY_TREE):
      return "BinaryTreeMaze";
    case(GROWING_TREE):
      return "GrowingTreeMaze";
    case(HUNT_KILL):
      return "HuntAndKillMaze";
    case(PRIMS):
      return "PrimsMaze";
    case(RECURSIVE_BACKTRACKER):
      return "RecursiveBacktrackerMaze";
    case(SIDE_WINDER):
      return "SideWinderMaze";
    case(WILSONS):
      return "WilsonsMaze";
    case(Size):
      break;
  }

  return ":) <-- Error";
}

Maze::Ptr MazeFactory::CreateMaze(MazeType maze_type, int width, int height)
{
  Maze::Ptr maze = GetMazeByType(maze_type, width, height);

  return maze;
}

Maze::Ptr MazeFactory::GenerateMaze(MazeType maze_type, int width, int height)
{
  Maze::Ptr maze = GetMazeByType(maze_type, width, height);
  maze->Generate();

  return maze;
}

Maze::Ptr MazeFactory::GetMazeByType(MazeType maze_type, int width, int height)
{
  switch(maze_type)
  {
    case(ALDOUS_BRODER):
      return std::make_shared<AldousBroderMaze>(width, height);
    case(BINARY_TREE):
      return std::make_shared<BinaryTreeMaze>(width, height);
    case(GROWING_TREE):
      return std::make_shared<GrowingTreeMaze>(width, height);
    case(HUNT_KILL):
      return std::make_shared<HuntAndKillMaze>(width, height);
    case(PRIMS):
      return std::make_shared<PrimsMaze>(width, height);
    case(RECURSIVE_BACKTRACKER):
      return std::make_shared<RecursiveBacktrackerMaze>(width, height);
    case(SIDE_WINDER):
     return std::make_shared<SideWinderMaze>(width, height);
    case(WILSONS):
     return std::make_shared<WilsonsMaze>(width, height);
    case(Size):
      break;
  }

  return std::make_shared<PrimsMaze>(width, height);
}

} // namespace maze
