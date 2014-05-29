// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/*
 * Copyright (C) 2014 Brandon Schaefer
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

#include "Main.h"

#include <sdl_backend/EntityCreator.h>
#include <sdl_backend/MainLoop.h>

#include <time.h>

#include <maze/MazeFactory.h>

namespace sbe = sdl_backend;

namespace sdl_maze
{

namespace
{
  int const WIDTH   = 800;
  int const HEIGHT  = 600;
  std::string TITLE = "SDL - Maze Generator";
}

Main::Main()
  : main_loop_(std::make_shared<sbe::MainLoop>(TITLE, WIDTH, HEIGHT))
  , main_layer_(std::make_shared<sbe::EntityLayer>())
{
  sbe::EntityCreator ec;

  main_loop_->world()->AddLayerToBottom(main_layer_);

  maze_main_ = std::make_shared<MazeMain>(ec.GetUniqueId(), main_loop_);
  main_layer_->AddEntity(maze_main_);

  main_loop_->StartMainLoop();
  main_layer_->Clear();
}

} // namespace sdl_maze

int main()
{
  // TEST
  //MazeFactory factory;
  //Maze::Ptr m = factory.GenerateMaze(WILSONS, 40, 75);
  //m->PrintMaze();

  srand(time(nullptr));

  sdl_maze::Main main;
}
