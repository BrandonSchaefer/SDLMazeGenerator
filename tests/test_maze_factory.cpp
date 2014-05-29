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

#include <gtest.h>
#include <maze/MazeFactory.h>

int const WIDTH = 10;
int const HEIGHT = 10;

class MockMazeFactory : public testing::Test
{
public:
  MockMazeFactory()
  {}

  maze::MazeFactory maze_factory;
};

TEST_F(MockMazeFactory, TestGenerateAldousBroder)
{
  maze::Maze::Ptr maze = maze_factory.GenerateMaze(maze::ALDOUS_BRODER, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(maze::ALDOUS_BRODER), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateBinaryTree)
{
  maze::Maze::Ptr maze = maze_factory.GenerateMaze(maze::BINARY_TREE, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(maze::BINARY_TREE), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateGrowingTree)
{
  maze::Maze::Ptr maze = maze_factory.GenerateMaze(maze::GROWING_TREE, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(maze::GROWING_TREE), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateHuntKill)
{
  maze::Maze::Ptr maze = maze_factory.GenerateMaze(maze::HUNT_KILL, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(maze::HUNT_KILL), maze->GetName());
}

TEST_F(MockMazeFactory, TestGeneratePrims)
{
  maze::Maze::Ptr maze = maze_factory.GenerateMaze(maze::PRIMS, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(maze::PRIMS), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateRecrsiveBacktracker)
{
  maze::Maze::Ptr maze = maze_factory.GenerateMaze(maze::RECURSIVE_BACKTRACKER, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(maze::RECURSIVE_BACKTRACKER), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateSideWinder)
{
  maze::Maze::Ptr maze = maze_factory.GenerateMaze(maze::SIDE_WINDER, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(maze::SIDE_WINDER), maze->GetName());
}

TEST_F(MockMazeFactory, TestGenerateWilsons)
{
  maze::Maze::Ptr maze = maze_factory.GenerateMaze(maze::WILSONS, WIDTH, HEIGHT);
  EXPECT_EQ(maze_factory.GetMazeTitle(maze::WILSONS), maze->GetName());
}
