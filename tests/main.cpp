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

#include <maze/AldousBroderMaze.h>
#include <maze/BinaryTreeMaze.h>
#include <maze/GrowingTreeMaze.h>
#include <maze/HuntAndKillMaze.h>
#include <maze/RecursiveBacktrackerMaze.h>
#include <maze/PrimsMaze.h>
#include <maze/SideWinderMaze.h>
#include <maze/WilsonsMaze.h>
#include <maze/Solver.h>

#include <assert.h>
#include <chrono>
#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

int const X = 40;
int const Y = 80;

void time_maze(Maze& maze)
{
  auto st = std::chrono::system_clock::now();

  maze.Generate();

  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - st);
  std::cout << elapsed.count() << " ms\t:" << maze.GetName() << std::endl;
}

void print_maze(Maze& maze)
{
  maze.PrintMaze();
}
void test_maze_generates_solvable_path(maze::Maze& maze)
{
  maze::Solver s;
  vector<Point> path = s.DFSolve(maze);

  assert(maze.IsStart(path.front()));
  assert(maze.IsFinish(path.back()));

  for (auto p : path)
    assert(maze.InBounds(p));
}

int main()
{
  srand(time(NULL));

  vector<Maze*> mazes;

  maze::RecursiveBacktrackerMaze rmaze(X, Y);
  mazes.push_back(&rmaze);

  maze::WilsonsMaze wmaze(X, Y);
  mazes.push_back(&wmaze);

  maze::SideWinderMaze smaze(X, Y);
  mazes.push_back(&smaze);

  maze::HuntAndKillMaze hkmaze(X, Y);
  mazes.push_back(&hkmaze);

  maze::AldousBroderMaze abmaze(X, Y);
  mazes.push_back(&abmaze);

  maze::GrowingTreeMaze gtmaze(X, Y);
  mazes.push_back(&gtmaze);

  maze::PrimsMaze pmaze(X, Y);
  mazes.push_back(&pmaze);

  maze::BinaryTreeMaze bmaze(X, Y);
  mazes.push_back(&bmaze);

  for (auto maze : mazes)
  {
    time_maze(*maze);
    test_maze_generates_solvable_path(*maze);
  }

  //for (auto maze : mazes)
    //print_maze(*maze);
}
