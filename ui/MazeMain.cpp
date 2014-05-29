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

#include <SDL2/SDL_image.h>

#include "config.h"
#include "MazeMain.h"

#include <sdl_backend/Color.h>
#include <sdl_backend/EntityCreator.h>

namespace sdl_maze
{

namespace
{
}

/*

|--------------------------------------|
|                                      |
|           Top Menu                   |
|--------------------------------------|
|                                      |
|                                      |
|                                      |
|         |---------|                  |
|         | EscMenu |                  |
|         |---------|                  |
|                                      |
|                                      |
|                                      |
|        Maze                          |
|                                      |
|                                      |
|                                      |
|--------------------------------------|

TopMenu.cpp
PauseMenu.cpp

// Who holds the actual maze::ptr?
MazeController.cpp <-- Holds the actual maze::ptr, which will then update the MazeEntity.cpp
MazeEntity.cpp <-- Holds a grid of cell states?
?Cell? (RenderableGeo)


*/

MazeMain::MazeMain(unsigned id, sbe::MainLoop::Ptr const& main_loop)
  : Entity(id)
  , main_loop_(main_loop)
  , game_layer_(std::make_shared<sbe::EntityLayer>())
{
  //sbe::Rect const& bound = main_loop_->world()->Boundary();

  //game_layer_->Hide();

  main_loop_->world()->AddLayerToMiddle(game_layer_);
}

MazeMain::~MazeMain()
{
  game_layer_->Clear();
}

void MazeMain::UpdatePosition(sbe::World::Ptr const& world)
{
}

void MazeMain::Update(float delta_time)
{
}

void MazeMain::Draw(sbe::GraphicsRenderer* graphics)
{

  graphics->SetRenderColor(sbe::color::WHITE);
  SDL_Rect dest = {0, 0, graphics->Width(), graphics->Height()};
  SDL_RenderFillRect(graphics->Renderer(), &dest);
}

} // namespace sdl_maze
